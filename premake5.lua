workspace "Fazel"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

-- bin\$(Configuration)-$(Platform)\$(ProjectName)\
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative the root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Fazel/vendor/GLFW/include"

-- same as #include <Fazel/vendor/GLFW/premake5.lua>
include "Fazel/vendor/GLFW"

project "Fazel"
	location "Fazel"
	kind "SharedLib"
	language "C++"
	-- bin/Debug-windows-x64/Fazel
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	-- bin-int/Debug-windows-x64/Fazel
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fzpch.h"
	pchsource "Fazel/src/fzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FZ_PLATFORM_WINDOWS",
			"FZ_BUILD_DLL",
			-- "FZ_ENABLE_ASSERTS"
		}

		-- %[..] is to make path relative to project correctly (take absolute path)
		-- %{!..} is to force path to be absolute.
		postbuildcommands
		{
			"{MKDIR} %[bin/" .. outputdir .. "/Sandbox]",
			"{COPYFILE} %[%{!cfg.buildtarget.abspath}] %[bin/" .. outputdir .. "/Sandbox]"
		}

	filter "configurations:Debug"
		defines "FZ_DEBUG"
		symbols "On"
		buildoptions "/utf-8"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines "FZ_RELEASE"
		optimize "On"
		buildoptions "/utf-8"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "FZ_DEBUG"
		optimize "On"
		buildoptions "/utf-8"
		buildoptions "/MD"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	-- bin/Debug-windows-x64/Sandbox/
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	-- bin-int/Debug-windows-x64/Sandbox/
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Fazel/vendor/spdlog/include",
		"Fazel/src"
	}

	links
	{
		"Fazel"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FZ_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "FZ_DEBUG"
		symbols "On"
		buildoptions "/utf-8"

	filter "configurations:Release"
		defines "FZ_RELEASE"
		optimize "On"
		buildoptions "/utf-8"

	filter "configurations:Dist"
		defines "FZ_DEBUG"
		optimize "On"
		buildoptions "/utf-8"