#include "Precompiled.h"
#include "GLShader.h"

#include "SemperEngine/Core/Assert.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace SemperEngine
{
	GLShader::GLShader(const ShaderManager::ShaderSource& shaderSource)
	{
		m_RendererID = CreateShader(shaderSource.vertexSource, shaderSource.fragmentSource);
	}
	GLShader::~GLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void GLShader::Bind() const noexcept
	{
		glUseProgram(m_RendererID);
	}

	// UnBinding should only be used in Debug 
	void GLShader::UnBind() const noexcept
	{
		glUseProgram(0);
	}

	void *GLShader::GetNativeHandle() const noexcept
	{
		return reinterpret_cast<void *>(m_RendererID);
	}
	const std::string &GLShader::GetName() const noexcept
	{
		return m_Name;
	}

	void GLShader::SetUniformMat2f(const std::string &name, const glm::mat2 &matrix)
	{
		glUniformMatrix2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void GLShader::SetUniformMat3f(const std::string &name, const glm::mat3 &matrix)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void GLShader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void GLShader::SetUniformInt(const std::string &name, int value)
	{
		glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}
	void GLShader::SetUniformInt2(const std::string &name, const glm::ivec2 &values)
	{
		glUniform2i(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y);
	}
	void GLShader::SetUniformInt3(const std::string &name, const glm::ivec3 &values)
	{
		glUniform3i(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z);
	}
	void GLShader::SetUniformInt4(const std::string &name, const glm::ivec4 &values)
	{
		glUniform4i(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z, values.w);
	}

	void GLShader::SetUniformFloat(const std::string &name, float value)
	{
		glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}
	void GLShader::SetUniformFloat2(const std::string &name, const glm::fvec2 &values)
	{
		glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y);
	}
	void GLShader::SetUniformFloat3(const std::string &name, const glm::fvec3 &values)
	{
		glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z);
	}
	void GLShader::SetUniformFloat4(const std::string &name, const glm::fvec4 &values)
	{
		glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z, values.w);
	}

	void GLShader::SetUniformDouble(const std::string &name, double value)
	{
		glUniform1d(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}
	void GLShader::SetUniformDouble2(const std::string &name, const glm::dvec2 &values)
	{
		glUniform2d(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y);
	}
	void GLShader::SetUniformDouble3(const std::string &name, const glm::dvec3 &values)
	{
		glUniform3d(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z);
	}
	void GLShader::SetUniformDouble4(const std::string &name, const glm::dvec4 &values)
	{
		glUniform4d(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z, values.w);
	}

	void GLShader::SetUniformIntArray(const std::string &name, int *values, U32 count)
	{
		glUniform1iv(glGetUniformLocation(m_RendererID, name.c_str()), count, values);
	}
	void GLShader::SetUniformFloatArray(const std::string &name, float *values, U32 count)
	{
		glUniform1fv(glGetUniformLocation(m_RendererID, name.c_str()), count, values);
	}
	void GLShader::SetUniformDoubleArray(const std::string &name, double *values, U32 count)
	{
		glUniform1dv(glGetUniformLocation(m_RendererID, name.c_str()), count, values);
	}

	U32 GLShader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
	{
		U32 shaderProgram = glCreateProgram();
		std::string errorLog;

		U32 vertexProgram = TryCompileShader(GL_VERTEX_SHADER, vertexShader, errorLog);
		SE_ASSERT_MSG(vertexProgram, errorLog.c_str());

		errorLog.clear();

		U32 fragmentProgram = TryCompileShader(GL_FRAGMENT_SHADER, fragmentShader, errorLog);
		SE_ASSERT_MSG(fragmentProgram, errorLog.c_str());

		glAttachShader(shaderProgram, vertexProgram);
		glAttachShader(shaderProgram, fragmentProgram);

		glLinkProgram(shaderProgram);
		glValidateProgram(shaderProgram);

		glDeleteShader(vertexProgram);
		glDeleteShader(fragmentProgram);

		return shaderProgram;
	}
	U32 GLShader::TryCompileShader(U32 shaderType, const std::string &shaderSource, std::string &errorLog)
	{
		U32 shaderID = glCreateShader(shaderType);
		const char *src = shaderSource.c_str();

		glShaderSource(shaderID, 1, &src, nullptr);
		glCompileShader(shaderID);

		int result;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			int errorLength;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errorLength);

			char *message = (char *) _alloca(errorLength * sizeof(char));
			glGetShaderInfoLog(shaderID, errorLength, &errorLength, message);

			errorLog = "Failed to compile" + std::string((shaderType == GL_VERTEX_SHADER) ? "vertex" : "fragment") + 
				" shader: \n" + std::string(message);

			glDeleteShader(shaderType);
			return 0;
		}
		return shaderID;
	}
}