#include "ApplicationLayer.h"

#include <imgui/imgui.h>


ApplicationLayer::ApplicationLayer() : 
	Layer("Application Layer")
{
	SemperEngine::Renderer::SetClearColor({ 0.7f, 0.7f,0.7f, 0.7f });

	float vertices[] = {
		// Position		TexCoords
		-0.5f, -0.5f,	0.0f, 0.0f, 
		 0.5f, -0.5f,   1.0f, 0.0f, 
		 0.5f,  0.5f,   1.0f, 1.0f,
		-0.5f,  0.5f,   0.0f, 1.0f
	};
	uint8_t indices[] = { 0, 1, 2, 2, 3, 0 };

	std::string vertexShader = {
		"#version 450 core\n"
		"layout(location = 0) in vec2 a_Position;\n"
		"layout(location = 1) in vec2 a_TexCoords;\n"
		"out vec2 v_TexCoords;\n"
		"void main()\n"
		"{\n"
		"v_TexCoords = a_TexCoords;\n"
		"gl_Position = vec4(a_Position, 0.0, 1.0);\n"
		"}\n"
	};
	std::string fragmentShader = {
		"#version 450 core\n"
		"layout(location = 0) out vec4 o_Color;\n"
		"in vec2 v_TexCoords;"
		"uniform sampler2D u_Texture;\n"
		"void main()\n"
		"{\n"
		"o_Color = texture(u_Texture, v_TexCoords);\n"
		"}\n"
	};
	
	m_Shader = SemperEngine::Shader::Create({ vertexShader, fragmentShader });
	m_Shader->Bind();
	m_Shader->SetUniformInt("u_Texture", 0);
	
	SemperEngine::TextureData data;
	data.minFilter = SemperEngine::TextureFilter::Nearest;
	data.magFilter = SemperEngine::TextureFilter::Nearest;
	m_BackgroundTexture = SemperEngine::Texture2D::Create("StoneTex.jpg", data);
	m_BackgroundTexture->Bind();

	m_IndexBuffer = SemperEngine::IndexBuffer::Create(indices, SemperEngine::IndexFormat::Uint8, sizeof(indices), SemperEngine::BufferUsage::Static);
	m_VertexBuffer = SemperEngine::VertexBuffer::Create(vertices, sizeof(vertices), SemperEngine::BufferUsage::Static);

	m_VertexBuffer->AddAttribute({ "u_Position", SemperEngine::VertexFormat::Float2, false });
	m_VertexBuffer->AddAttribute({ "u_TexCoords", SemperEngine::VertexFormat::Float2, false });

	m_VertexArray = SemperEngine::VertexArray::Create(m_VertexBuffer, m_IndexBuffer);
}

void ApplicationLayer::OnAttach()
{
}

void ApplicationLayer::OnDetach()
{
}

void ApplicationLayer::OnUpdate(float deltaTime)
{
	SemperEngine::Renderer::Clear();

	m_BackgroundTexture->Bind();
	SemperEngine::Renderer::DrawIndexed(m_VertexArray, m_Shader);
}

void ApplicationLayer::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::Text("Hello, World!");
	ImGui::ColorEdit4("Color", m_Color);
	ImGui::End();
}

void ApplicationLayer::OnEvent(SemperEngine::Event &e)
{
}
