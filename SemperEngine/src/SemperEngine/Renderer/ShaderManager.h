#pragma once
#include "SemperEngine/Core/Types.h"
#include "Shader.h"

#include <unordered_map>


namespace SemperEngine
{
	struct ShaderSource
	{
		std::string vertexSource;
		std::string fragmentSource;
	};

	class ShaderManager
	{
	public:
		ShaderManager() = default;
		~ShaderManager() = default;

		void AddShader(const std::string &name, Shader *shader);
		Shader *GetShader(const std::string &name);

		void Remove(const std::string &name);
		void ClearShader();

		Shader *operator [](const std::string &name) noexcept;

		static ShaderSource LoadFromFile(const std::string &filepath);
		static ShaderSource LoadFromFiles(const std::string &vertexPath, const std::string &fragmentPath);

	private:
		std::unordered_map<std::string, Shader *> m_ShaderStorage;
	};
}