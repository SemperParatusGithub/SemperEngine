#include "ApplicationLayer.h"

#include <imgui/imgui.h>


ApplicationLayer::ApplicationLayer() : 
	Layer("Application Layer")
{
	SemperEngine::Renderer::SetClearColor({ 0.7f, 0.7f,0.7f, 0.7f });

	float vertices[] = {
		// Position		Color
		-0.5f, -0.5f,	1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f,  0.5f,   0.0f, 0.0f, 1.0f, 1.0f
	};
	uint8_t indices[] = { 0, 1, 2 };

	std::string vertexShader = {
		"#version 450 core\n"
		"layout(location = 0) in vec2 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"out vec4 v_Color;\n"
		"void main()\n"
		"{\n"
		"v_Color = color;\n"
		"gl_Position = vec4(position, 0.0, 1.0);\n"
		"}\n"
	};
	std::string fragmentShader = {
		"#version 450 core\n"
		"in vec4 v_Color;"
		"out vec4 o_Color;\n"
		"void main()\n"
		"{\n"
		"o_Color = v_Color;\n"
		"}\n"
	};

	m_Shader = SemperEngine::Shader::Create({ vertexShader, fragmentShader });

	m_IndexBuffer = SemperEngine::IndexBuffer::Create(indices, SemperEngine::IndexFormat::Uint8, sizeof(indices));
	m_VertexBuffer = SemperEngine::VertexBuffer::Create(vertices, sizeof(vertices));
	m_VertexBuffer->AddElement({ "u_Position", SemperEngine::VertexFormat::Float2, false });
	m_VertexBuffer->AddElement({ "u_Color", SemperEngine::VertexFormat::Float4, false });

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
	// m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
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
