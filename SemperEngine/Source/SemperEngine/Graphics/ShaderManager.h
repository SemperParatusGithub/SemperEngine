#pragma once
#include "SemperEngine/Core/Types.h"

#include <unordered_map>


namespace SemperEngine
{
	class Shader;

	class ShaderManager
	{
	public:
		struct ShaderSource
		{
			std::string vertexSource;
			std::string fragmentSource;
		};

	public:
		ShaderManager() = default;
		~ShaderManager() = default;

		void AddShader(ConstRef<std::string> name, SharedPtr<Shader> shader);
		SharedPtr<Shader> GetShader(ConstRef<std::string> name);

		void Remove(ConstRef<std::string> name);
		void ClearShader();

		SharedPtr<Shader> operator [](ConstRef<std::string> name) noexcept;

		static ShaderSource LoadFromFile(ConstRef<std::string> filepath);
		static ShaderSource LoadFromFiles(ConstRef<std::string> vertexPath, ConstRef<std::string> fragmentPath);

	private:
		std::unordered_map<std::string, SharedPtr<Shader>> m_ShaderStorage;
	};
}