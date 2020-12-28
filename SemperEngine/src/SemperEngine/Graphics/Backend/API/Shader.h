#pragma once
#include "SemperEngine/Graphics/ShaderManager.h"

#include <glm/glm.hpp>


namespace SemperEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		static Shader *Create(const ShaderManager::ShaderSource &shaderSource);

		virtual void Bind() const noexcept = 0;
		virtual void UnBind() const noexcept = 0;

		virtual void *GetNativeHandle()	const noexcept = 0;
		virtual const std::string &GetName() const noexcept = 0;

		virtual void SetUniformMat2f(const std::string &name, const glm::mat2 &matrix) = 0;
		virtual void SetUniformMat3f(const std::string &name, const glm::mat3 &matrix) = 0;
		virtual void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) = 0;

		virtual void SetUniformInt(const std::string &name, int value) = 0;
		virtual void SetUniformInt2(const std::string &name, const glm::ivec2& values) = 0;
		virtual void SetUniformInt3(const std::string &name, const glm::ivec3& values) = 0;
		virtual void SetUniformInt4(const std::string &name, const glm::ivec4& values) = 0;

		virtual void SetUniformFloat(const std::string &name, float value) = 0;
		virtual void SetUniformFloat2(const std::string &name, const glm::fvec2 &values) = 0;
		virtual void SetUniformFloat3(const std::string &name, const glm::fvec3 &values) = 0;
		virtual void SetUniformFloat4(const std::string &name, const glm::fvec4 &values) = 0;

		virtual void SetUniformDouble(const std::string &name, double value) = 0;
		virtual void SetUniformDouble2(const std::string &name, const glm::dvec2 &values) = 0;
		virtual void SetUniformDouble3(const std::string &name, const glm::dvec3 &values) = 0;
		virtual void SetUniformDouble4(const std::string &name, const glm::dvec4 &values) = 0;

		virtual void SetUniformIntArray(const std::string &name, int *values, U32 count) = 0;
		virtual void SetUniformFloatArray(const std::string &name, float *values, U32 count) = 0;
		virtual void SetUniformDoubleArray(const std::string &name, double *values, U32 count) = 0;
	};
}