workspace "SemperEngine"
	architecture "x86_64"
	startproject "Editor"

	configurations 	{ "Debug", "Release", "Dist" }
	flags 			{ "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "../SemperEngine/vendor/GLFW"
	include "../SemperEngine/vendor/Glad"
	include "../SemperEngine/vendor/imgui"
group ""

group "Engine"
	include "../SemperEngine"
group ""

group "Application"
	include "../Application"
group ""

group "Editor"
	include "../Editor"
group ""
