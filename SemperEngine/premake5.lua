project "SemperEngine"
	location "../Scripts/Build"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
    staticruntime "on"

	targetdir   ("../Binaries/" .. outputdir)
	objdir      ("../Binaries/Intermediate/" .. outputdir)

	pchheader "Precompiled.h"
	pchsource "Source/Precompiled.cpp"

	files
	{
		-- Source Files
		"Source/**.h",
		"Source/**.cpp",

		-- Cereal
		"External/cereal/include/cereal/**.h",
		"External/cereal/include/cereal/**.hpp",
		"External/cereal/include/cereal/**.cpp",

		-- entt
		"External/entt/include/entt.hpp",

		-- glm
		"External/glm/glm/**.hpp",
		"External/glm/glm/**.inl",
		
		-- ImGuizmo
		"External/ImGuizmo/ImGuizmo.h",
		"External/ImGuizmo/ImGuizmo.cpp",
		
		-- STB
		"External/stb_image/**.h",
		"External/stb_image/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"Source",
		"Source/SemperEngine/Graphics/ImGui",
		"Source/SemperEngine/Graphics/Backend",

		"../SemperEngine/External/GLFW/include",
		"../SemperEngine/External/Glad/include",
		"../SemperEngine/External/imgui",		
        "../SemperEngine/External/glm",
        "../SemperEngine/External/stb_image",
		"../SemperEngine/External/entt/include",
		"../SemperEngine/External/ImGuizmo",
		"../SemperEngine/External/cereal/include",
		"../SemperEngine/External/assimp/include"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	postbuildcommands 
	{		
		'{COPY} "../../Editor/Assets" "%{cfg.targetdir}/Assets"'
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "SE_DEBUG"
		runtime "Debug"
		symbols "on"
		postbuildcommands
		{
			'{COPY} "../../SemperEngine/External/assimp/bin/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"',
			'{COPY} "../../SemperEngine/External/assimp/bin/Debug/assimp-vc141-mtd.lib" "%{cfg.targetdir}"'
		}

	filter "configurations:Release"
		defines "SE_RELEASE"
		runtime "Release"
		optimize "on"
		postbuildcommands
		{
			'{COPY} "../../SemperEngine/External/assimp/bin/Release/assimp-vc141-mt.dll" "%{cfg.targetdir}"',
			'{COPY} "../../SemperEngine/External/assimp/bin/Release/assimp-vc141-mt.lib" "%{cfg.targetdir}"'
		}

	filter "configurations:Production"
		defines "SE_PRODUCTION"
		runtime "Release"
		optimize "on"
		postbuildcommands
		{
			'{COPY} "../../SemperEngine/External/assimp/bin/Release/assimp-vc141-mt.dll" "%{cfg.targetdir}"',
			'{COPY} "../../SemperEngine/External/assimp/bin/Release/assimp-vc141-mt.lib" "%{cfg.targetdir}"'
		}