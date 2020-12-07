project "Application"
	location "../Scripts/build"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir	("../bin/" 		.. outputdir .. "/%{prj.name}")
	objdir 		("../bin-int/" 	.. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"../SemperEngine/src",
		"../SemperEngine/vendor",
		"../SemperEngine/vendor/glm",
		"../SemperEngine/vendor/entt/include",
		"../SemperEngine/vendor/Glad/include"
	}

	links
	{
		"SemperEngine",
		"Glad"
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
