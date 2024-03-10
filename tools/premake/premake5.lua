local path = require "./path"
PROJECT_NAME = path.getProjectName( 2 )

workspace (PROJECT_NAME)
	configurations { "Debug", "Release", "Final" }
	platforms { "x64", "x86" }
	location "../../"

project (PROJECT_NAME)
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	
	targetname (PROJECT_NAME .. "_%{cfg.buildcfg}")

	targetdir "../../bin"
	objdir "../../bin/obj/"

	location "../../build"

	includedirs { 
		"../../src",
		"../../dependencies/assimp/include" 
	}
	libdirs { "../../dependencies/assimp/lib" }

	files { 
		"../../src/**.h", 
		"../../src/**.cpp",
		"../../src/**.hpp"
	}

	links { "assimp-vc143-mt.lib", "zlibstatic.lib" }

	filter "configurations:Debug"
      defines { "DEBUG" }
	  
	  filter "configurations:Release"
      defines { "NDEBUG", "RELEASE" }
	  optimize "On"
	 
	filter "configurations:Final"
      defines { "FINAL" }
	  symbols "Off"
	  optimize "Full"
	
