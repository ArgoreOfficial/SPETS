
PROJECT_NAME = "SPETS"

workspace (PROJECT_NAME)
	configurations { "Debug", "Release", "Final" }
	platforms { "x64", "x86" }
	location "../../"
	startproject (PROJECT_NAME)

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
		"../../libs/assimp/include" ,
		"../../libs/glad/include/", 
		"../../libs/glfw/include/", 
		"../../libs/glm/", 
		"../../libs/imgui/", 
		"../../libs/imgui/examples" 
	}
	libdirs { "../../libs/assimp/lib" }

	files { 
		"../../src/**.h", 
		"../../src/**.cpp",
		"../../src/**.hpp"
	}

	links { "assimp-vc143-mt.lib", "zlibstatic.lib", "GLFW", "GLM", "GLAD", "ImGui" }

	filter "configurations:Debug"
      defines { "DEBUG" }
	  
	  filter "configurations:Release"
      defines { "NDEBUG", "RELEASE" }
	  optimize "On"
	 
	filter "configurations:Final"
      defines { "FINAL" }
	  symbols "Off"
	  optimize "Full"

	filter "system:windows"
	  defines { "_WINDOWS" }
	
group "Dependencies"

include "../../libs/glfw.lua"
include "../../libs/glad.lua"
include "../../libs/glm.lua"
include "../../libs/imgui.lua"