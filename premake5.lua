workspace "CSnake"
	architecture "x86_64"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "CSnake"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	location "CSnake"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"CSnake/src/**.h",
		"CSnake/src/**.cpp"
	}

	includedirs{
		"CSnake/src"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

