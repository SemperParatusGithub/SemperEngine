project "Editor"
	location "../Scripts/Build"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir   ("../Binaries/" .. outputdir)
	objdir      ("../Binaries/Intermediate/" .. outputdir)

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs
	{
		"../SemperEngine/Source",
		"../SemperEngine/External",
		"../SemperEngine/External/glm",
		"../SemperEngine/External/Glad/include",
		"../SemperEngine/External/GLFW/include",
		"../SemperEngine/External/cereal/include"
	}

	links { "SemperEngine" }

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

	filter "configurations:Production"
		defines "SE_PRODUCTION"
		runtime "Release"
		optimize "on"
