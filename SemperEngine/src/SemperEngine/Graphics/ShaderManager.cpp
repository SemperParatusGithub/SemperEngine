#include "Precompiled.h"
#include "ShaderManager.h"

#include "SemperEngine/Core/Assert.h"
#include "SemperEngine/Graphics/Backend/OpenGL/GLShader.h"

#include <string>
#include <fstream>


namespace SemperEngine
{
	void ShaderManager::AddShader(const std::string &name, Shader *shader)
	{
		m_ShaderStorage[name] = shader;
	}
	Shader *ShaderManager::GetShader(const std::string &name)
	{
		return m_ShaderStorage[name];
	}

	void ShaderManager::Remove(const std::string &name)
	{
		m_ShaderStorage.erase(name);
	}
	void ShaderManager::ClearShader()
	{
		m_ShaderStorage.clear();
	}

	Shader *ShaderManager::operator[](const std::string &name) noexcept
	{
		return m_ShaderStorage[name];
	}

	ShaderManager::ShaderSource ShaderManager::LoadFromFile(const std::string &filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
			{
				ss[(int) type] << line << "\n";
			}
		}
		return { ss[(int) ShaderType::VERTEX].str(), ss[(int) ShaderType::FRAGMENT].str() };
	}

	ShaderManager::ShaderSource ShaderManager::LoadFromFiles(const std::string &vertexPath, const std::string &fragmentPath)
	{
		std::ifstream vertexStream(vertexPath);
		std::ifstream fragmentStream(fragmentPath);

		std::string vertexSource((std::istreambuf_iterator<char>(vertexStream)),
			(std::istreambuf_iterator<char>()));

		std::string fragmentSource((std::istreambuf_iterator<char>(fragmentStream)),
			(std::istreambuf_iterator<char>()));

		return { vertexSource, fragmentSource };
	}
}