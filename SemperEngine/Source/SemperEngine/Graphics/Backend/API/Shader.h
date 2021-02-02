#pragma once
#include "SemperEngine/Graphics/ShaderManager.h"

#include <glm/glm.hpp>


namespace SemperEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		static Shader *Create(ConstRef<ShaderManager::ShaderSource> shaderSource);

		virtual void Bind() const noexcept = 0;
		virtual void UnBind() const noexcept = 0;

		virtual void *GetNativeHandle()	const noexcept = 0;
		virtual ConstRef<std::string> GetName() const noexcept = 0;

		virtual void SetUniformMat2f(ConstRef<std::string> name, ConstRef<Mat2> matrix) = 0;
		virtual void SetUniformMat3f(ConstRef<std::string> name, ConstRef<Mat3> matrix) = 0;
		virtual void SetUniformMat4f(ConstRef<std::string> name, ConstRef<Mat4> matrix) = 0;

		virtual void SetUniformInt(ConstRef<std::string> name, int value) = 0;
		virtual void SetUniformInt2(ConstRef<std::string> name, ConstRef<Vec2i> values) = 0;
		virtual void SetUniformInt3(ConstRef<std::string> name, ConstRef<Vec3i> values) = 0;
		virtual void SetUniformInt4(ConstRef<std::string> name, ConstRef<Vec4i> values) = 0;

		virtual void SetUniformFloat(ConstRef<std::string> name, float value) = 0;
		virtual void SetUniformFloat2(ConstRef<std::string> name, ConstRef<Vec2f> values) = 0;
		virtual void SetUniformFloat3(ConstRef<std::string> name, ConstRef<Vec3f> values) = 0;
		virtual void SetUniformFloat4(ConstRef<std::string> name, ConstRef<Vec4f> values) = 0;

		virtual void SetUniformDouble(ConstRef<std::string> name, double value) = 0;
		virtual void SetUniformDouble2(ConstRef<std::string> name, ConstRef<Vec2d> values) = 0;
		virtual void SetUniformDouble3(ConstRef<std::string> name, ConstRef<Vec3d> values) = 0;
		virtual void SetUniformDouble4(ConstRef<std::string> name, ConstRef<Vec4d> values) = 0;

		virtual void SetUniformIntArray(ConstRef<std::string> name, int *values, U32 count) = 0;
		virtual void SetUniformFloatArray(ConstRef<std::string> name, float *values, U32 count) = 0;
		virtual void SetUniformDoubleArray(ConstRef<std::string> name, double *values, U32 count) = 0;
	};
}