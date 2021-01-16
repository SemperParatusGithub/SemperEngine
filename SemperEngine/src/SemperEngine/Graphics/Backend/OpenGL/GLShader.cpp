#include "Precompiled.h"
#include "GLShader.h"

#include "SemperEngine/Core/Assert.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace SemperEngine
{
	GLShader::GLShader(ConstRef<ShaderManager::ShaderSource> shaderSource)
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

	void GLShader::SetUniformMat2f(ConstRef<std::string> name, ConstRef<Mat2> matrix)
	{
		glUniformMatrix2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void GLShader::SetUniformMat3f(ConstRef<std::string> name, ConstRef<Mat3> matrix)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void GLShader::SetUniformMat4f(ConstRef<std::string> name, ConstRef<Mat4> matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void GLShader::SetUniformInt(ConstRef<std::string> name, int value)
	{
		glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}
	void GLShader::SetUniformInt2(ConstRef<std::string> name, ConstRef<Vec2i> values)
	{
		glUniform2i(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y);
	}
	void GLShader::SetUniformInt3(ConstRef<std::string> name, ConstRef<Vec3i> values)
	{
		glUniform3i(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z);
	}
	void GLShader::SetUniformInt4(ConstRef<std::string> name, const ConstRef<Vec4i> values)
	{
		glUniform4i(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z, values.w);
	}

	void GLShader::SetUniformFloat(ConstRef<std::string> name, float value)
	{
		glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}
	void GLShader::SetUniformFloat2(ConstRef<std::string> name, ConstRef<Vec2f> values)
	{
		glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y);
	}
	void GLShader::SetUniformFloat3(ConstRef<std::string> name, ConstRef<Vec3f> values)
	{
		glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z);
	}
	void GLShader::SetUniformFloat4(ConstRef<std::string> name, ConstRef<Vec4f> values)
	{
		glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z, values.w);
	}

	void GLShader::SetUniformDouble(ConstRef<std::string> name, double value)
	{
		glUniform1d(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}
	void GLShader::SetUniformDouble2(ConstRef<std::string> name, ConstRef<Vec2d> values)
	{
		glUniform2d(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y);
	}
	void GLShader::SetUniformDouble3(ConstRef<std::string> name, ConstRef<Vec3d> values)
	{
		glUniform3d(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z);
	}
	void GLShader::SetUniformDouble4(ConstRef<std::string> name, ConstRef<Vec4d> values)
	{
		glUniform4d(glGetUniformLocation(m_RendererID, name.c_str()), values.x, values.y, values.z, values.w);
	}

	void GLShader::SetUniformIntArray(ConstRef<std::string> name, int *values, U32 count)
	{
		glUniform1iv(glGetUniformLocation(m_RendererID, name.c_str()), count, values);
	}
	void GLShader::SetUniformFloatArray(ConstRef<std::string> name, float *values, U32 count)
	{
		glUniform1fv(glGetUniformLocation(m_RendererID, name.c_str()), count, values);
	}
	void GLShader::SetUniformDoubleArray(ConstRef<std::string> name, double *values, U32 count)
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

			char *message = new char[errorLength * sizeof(char)];
			glGetShaderInfoLog(shaderID, errorLength, &errorLength, message);

			errorLog = "Failed to compile" + std::string((shaderType == GL_VERTEX_SHADER) ? "vertex" : "fragment") + 
				" shader: \n" + std::string(message);

			glDeleteShader(shaderType);
			delete[] message;
			return 0;
		}
		return shaderID;
	}
}