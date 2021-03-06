#include "Precompiled.h"
#include "GLBackend.h"

#include "GLIndexBuffer.h"

#include <glad/glad.h>


namespace SemperEngine
{
	static void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			SE_CORE_ERROR("[OpenGL Debug HIGH] %s", message);
			SE_ASSERT_MSG(false, "GL_DEBUG_SEVERITY_HIGH");
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			SE_CORE_WARN("[OpenGL Debug MEDIUM] %s", message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			SE_CORE_INFO("[OpenGL Debug LOW] %s", message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			//SE_CORE_INFO("[OpenGL Debug NOTIFICATION] %s", message);
			break;
		}
	}

	void GLBackend::Init()
	{
		glDebugMessageCallback(OpenGLLogMessage, nullptr);
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);		
		//glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glFrontFace(GL_CCW);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_STENCIL_TEST);

		// Set Capabilties
		Backend::s_Capabilities.renderAPI = "OpenGL";
		Backend::s_Capabilities.vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
		Backend::s_Capabilities.renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
		Backend::s_Capabilities.version = reinterpret_cast<const char *>(glGetString(GL_VERSION));

		glGetIntegerv(GL_MAX_SAMPLES, &Backend::s_Capabilities.maxSamples);
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &Backend::s_Capabilities.maxTextureUnits);
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &Backend::s_Capabilities.maxAnisotropy);
	}

	void GLBackend::SetClearColor(ConstRef<Vec4> clearColor)
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	}

	void GLBackend::SetViewport(float x, float y, float width, float height)
	{
		glViewport(x, y, width, height);
	}

	void GLBackend::SetRenderMode(RenderMode mode)
	{
		if (mode == RenderMode::Default)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (mode == RenderMode::Lines)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
	}

	void GLBackend::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLBackend::DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader)
	{
		vertexArray->Bind();
		shader->Bind();
		IndexFormat indexFormat = vertexArray->GetIndexBuffer()->GetFormat();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GLTools::IndexFormatToGLType(indexFormat), nullptr);
	}
	void GLBackend::DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader, U32 count)
	{
		vertexArray->Bind();
		shader->Bind();
		IndexFormat indexFormat = vertexArray->GetIndexBuffer()->GetFormat();
		glDrawElements(GL_TRIANGLES, count, GLTools::IndexFormatToGLType(indexFormat), nullptr);
	}
}