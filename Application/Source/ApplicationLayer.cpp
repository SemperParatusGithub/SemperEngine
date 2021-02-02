#include "ApplicationLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/include/GLFW/glfw3.h>


ApplicationLayer::ApplicationLayer() : 
	Layer("Application Layer"),
	m_CameraController(1280.0f / 720.0f, 0, 0)
{
	Renderer::SetClearColor({ 0.7f, 0.7f,0.7f, 0.7f });

	float vertices[] = {
		// Position				TexCoords
		-0.5f, -0.5f, -0.1f,	0.0f, 0.0f, 
		 0.5f, -0.5f, -0.1f,	1.0f, 0.0f, 
		 0.5f,  0.5f, -0.1f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.1f,	0.0f, 1.0f
	};
	uint8_t indices[] = { 0, 1, 2, 2, 3, 0 };

	std::string textureVertexShader = {
		"#version 450 core\n"
		"layout(location = 0) in vec3 a_Position;\n"
		"layout(location = 1) in vec2 a_TexCoords;\n"
		"out vec2 v_TexCoords;\n"
		"uniform mat4 u_MVP;\n"
		"void main()\n"
		"{\n"
		"v_TexCoords = a_TexCoords;\n"
		"gl_Position = u_MVP * vec4(a_Position, 1.0);\n"
		"}\n"
	};
	std::string textureFragmentShader = {
		"#version 450 core\n"
		"layout(location = 0) out vec4 o_Color;\n"
		"in vec2 v_TexCoords;"
		"uniform sampler2D u_Texture;\n"
		"void main()\n"
		"{\n"
		"o_Color = texture(u_Texture, v_TexCoords);\n"
		"}\n"
	};

	std::string flatColorVertexShader = {
		"#version 450 core\n"
		"layout(location = 0) in vec3 a_Position;\n"
		"uniform mat4 u_MVP;\n"
		"void main()\n"
		"{\n"
		"gl_Position = u_MVP * vec4(a_Position, 1.0);\n"
		"}\n"
	};
	std::string flatColorFragmentShader = {
		"#version 450 core\n"
		"layout(location = 0) out vec4 o_Color;\n"
		"uniform vec4 u_Color;\n"
		"void main()\n"
		"{\n"
		"o_Color = u_Color;\n"
		"}\n"
	};
	
	m_Shader.reset(Shader::Create({ textureVertexShader, textureFragmentShader }));
	m_Shader->Bind();
	m_Shader->SetUniformInt("u_Texture", 0);

	m_FlatColorShader.reset(Shader::Create({ flatColorVertexShader, flatColorFragmentShader }));
	
	TextureData data;
	data.minFilter = TextureFilter::Linear;
	data.magFilter = TextureFilter::Linear;
	m_Texture.reset(Texture2D::Create("Grid.png", data));

	m_IndexBuffer.reset(IndexBuffer::Create(indices, IndexFormat::Uint8, sizeof(indices), BufferUsage::Static));
	m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices), BufferUsage::Static));

	m_VertexBuffer->AddAttribute({ "u_Position", VertexFormat::Float3, false });
	m_VertexBuffer->AddAttribute({ "u_TexCoords", VertexFormat::Float2, false });

	m_VertexArray.reset(VertexArray::Create(m_VertexBuffer.get(), m_IndexBuffer.get()));
}

void ApplicationLayer::OnAttach()
{
}

void ApplicationLayer::OnDetach()
{
}

void ApplicationLayer::OnUpdate(float deltaTime)
{
	m_CameraController.OnUpdate(deltaTime);

	Renderer::Clear();

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetUniformFloat4("u_Color", { m_Color[0],m_Color[1],m_Color[2],m_Color[3] });
	m_FlatColorShader->SetUniformMat4f("u_MVP", m_CameraController.GetCamera().GetProjectionView() * glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), { 0.0f, 0.0f, 1.0f }));
	Renderer::DrawIndexed(m_VertexArray, m_FlatColorShader);
	
	m_Texture->Bind();
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", m_CameraController.GetCamera().GetProjectionView() * glm::scale(glm::mat4(1.0f), { 10.0f, 10.0f, 1.0f }));
	Renderer::DrawIndexed(m_VertexArray, m_Shader);
}

void ApplicationLayer::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::Text("Hello, World!");
	ImGui::Text("Frame time: %.2f FPS", ImGui::GetIO().Framerate);
	ImGui::End();
}

void ApplicationLayer::OnEvent(Event &e)
{
	m_CameraController.OnEvent(e);
}