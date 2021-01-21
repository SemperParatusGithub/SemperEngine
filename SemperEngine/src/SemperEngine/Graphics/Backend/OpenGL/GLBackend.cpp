#include "Precompiled.h"
#include "GLBackend.h"

#include "GLIndexBuffer.h"

#include <glad/glad.h>


namespace SemperEngine
{
	void GLBackend::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);		  
	}

	void GLBackend::SetClearColor(ConstRef<glm::vec4> clearColor)
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	}

	void GLBackend::SetViewport(float x, float y, float width, float height)
	{
		glViewport(x, y, width, height);
	}

	void GLBackend::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	std::string GLBackend::GetRenderAPIString()
	{
		return std::string("OpenGL");
	}

	std::string GLBackend::GetVendor()
	{
		const char *string = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
		return std::string(string);
	}

	std::string GLBackend::GetRenderer()
	{
		const char *string = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
		return std::string(string);
	}

	std::string GLBackend::GetVersion()
	{
		const char *string = reinterpret_cast<const char *>(glGetString(GL_VERSION));
		return std::string(string);
	}

	void GLBackend::DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader)
	{
		vertexArray->Bind();
		shader->Bind();
		IndexFormat indexFormat = vertexArray->GetIndexBuffer()->GetFormat();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GLTools::IndexFormatToGLType(indexFormat), nullptr);
	}
}