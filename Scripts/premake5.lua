workspace "SemperEngine"
	architecture "x86_64"
	startproject "Editor"

	configurations 	{ "Debug", "Release", "Production" }
	flags 			{ "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "../SemperEngine/External/GLFW"
	include "../SemperEngine/External/Glad"
	include "../SemperEngine/External/imgui"
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
