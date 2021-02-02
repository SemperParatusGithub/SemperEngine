#pragma once
#include "SemperEngine/Graphics/Backend/API/Shader.h"
#include "GLTools.h"	

#include <unordered_map>


namespace SemperEngine
{
	class GLShader : public Shader
	{
	public:
		GLShader(ConstRef<ShaderManager::ShaderSource> shaderSource);
		~GLShader();

		virtual void Bind() const noexcept override;
		virtual void UnBind() const noexcept override;

		virtual void *GetNativeHandle()	const noexcept override;
		virtual const std::string &GetName() const noexcept override;

		virtual void SetUniformMat2f(ConstRef<std::string> name, ConstRef<Mat2> matrix) override;
		virtual void SetUniformMat3f(ConstRef<std::string> name, ConstRef<Mat3> matrix) override;
		virtual void SetUniformMat4f(ConstRef<std::string> name, ConstRef<Mat4> matrix) override;

		virtual void SetUniformInt(ConstRef<std::string> name, int value) override;
		virtual void SetUniformInt2(ConstRef<std::string> name, ConstRef<Vec2i> values) override;
		virtual void SetUniformInt3(ConstRef<std::string> name, ConstRef<Vec3i> values) override;
		virtual void SetUniformInt4(ConstRef<std::string> name, ConstRef<Vec4i> values) override;

		virtual void SetUniformFloat(ConstRef<std::string> name, float value) override;
		virtual void SetUniformFloat2(ConstRef<std::string> name, ConstRef<Vec2f> values) override;
		virtual void SetUniformFloat3(ConstRef<std::string> name, ConstRef<Vec3f> values) override;
		virtual void SetUniformFloat4(ConstRef<std::string> name, ConstRef<Vec4f> values) override;

		virtual void SetUniformDouble(ConstRef<std::string> name, double value) override;
		virtual void SetUniformDouble2(ConstRef<std::string> name, ConstRef<Vec2d> values) override;
		virtual void SetUniformDouble3(ConstRef<std::string> name, ConstRef<Vec3d> values) override;
		virtual void SetUniformDouble4(ConstRef<std::string> name, ConstRef<Vec4d> values) override;

		virtual void SetUniformIntArray(ConstRef<std::string> name, int *values, U32 count) override;
		virtual void SetUniformFloatArray(ConstRef<std::string> name, float *values, U32 count) override;
		virtual void SetUniformDoubleArray(ConstRef<std::string> name, double *values, U32 count) override;

	private:
		U32 CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
		U32 TryCompileShader(U32 shaderType, const std::string &shaderSource, std::string &errorLog);

	private:
		RendererID m_RendererID;
		std::string m_Name;
	};
}