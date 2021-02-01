project "SemperEngine"
	location "../Scripts/build"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
    staticruntime "on"

	targetdir   ("../bin/"      .. outputdir .. "/%{prj.name}")
	objdir      ("../bin-int/"  .. outputdir .. "/%{prj.name}")

	pchheader "Precompiled.h"
	pchsource "src/Precompiled.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",

		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",

		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",

		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src",
		"src/SemperEngine/Graphics/ImGui",
		"src/SemperEngine/Graphics/Backend",
        "../SemperEngine/vendor/GLFW/include",
        "../SemperEngine/vendor/Glad/include",
        "../SemperEngine/vendor/imgui",
        "../SemperEngine/vendor/glm",
        "../SemperEngine/vendor/stb_image",
		"../SemperEngine/vendor/entt/include",
		"../SemperEngine/vendor/ImGuizmo",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "SE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SE_DIST"
		runtime "Release"
		optimize "on"
