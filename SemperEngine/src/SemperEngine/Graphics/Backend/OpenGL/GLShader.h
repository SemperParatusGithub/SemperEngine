#pragma once
#include "SemperEngine/Graphics/Backend/API/Shader.h"
#include "GLTools.h"	

#include <unordered_map>


namespace SemperEngine
{
	class GLShader : public Shader
	{
	public:
		GLShader(const ShaderManager::ShaderSource &shaderSource);
		~GLShader();

		virtual void Bind() const noexcept override;
		virtual void UnBind() const noexcept override;

		virtual void *GetNativeHandle()	const noexcept override;
		virtual const std::string &GetName() const noexcept override;

		virtual void SetUniformMat2f(const std::string &name, const glm::mat2 &matrix) override;
		virtual void SetUniformMat3f(const std::string &name, const glm::mat3 &matrix) override;
		virtual void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) override;

		virtual void SetUniformInt(const std::string &name, int value) override;
		virtual void SetUniformInt2(const std::string &name, const glm::ivec2 &values) override;
		virtual void SetUniformInt3(const std::string &name, const glm::ivec3 &values) override;
		virtual void SetUniformInt4(const std::string &name, const glm::ivec4 &values) override;

		virtual void SetUniformFloat(const std::string &name, float value) override;
		virtual void SetUniformFloat2(const std::string &name, const glm::fvec2 &values) override;
		virtual void SetUniformFloat3(const std::string &name, const glm::fvec3 &values) override;
		virtual void SetUniformFloat4(const std::string &name, const glm::fvec4 &values) override;

		virtual void SetUniformDouble(const std::string &name, double value) override;
		virtual void SetUniformDouble2(const std::string &name, const glm::dvec2 &values) override;
		virtual void SetUniformDouble3(const std::string &name, const glm::dvec3 &values) override;
		virtual void SetUniformDouble4(const std::string &name, const glm::dvec4 &values) override;

		virtual void SetUniformIntArray(const std::string &name, int *values, U32 count) override;
		virtual void SetUniformFloatArray(const std::string &name, float *values, U32 count) override;
		virtual void SetUniformDoubleArray(const std::string &name, double *values, U32 count) override;

	private:
		U32 CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
		U32 TryCompileShader(U32 shaderType, const std::string &shaderSource, std::string &errorLog);

	private:
		RendererID m_RendererID;
		std::string m_Name;
	};
}