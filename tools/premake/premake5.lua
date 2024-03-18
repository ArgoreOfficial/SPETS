
PROJECT_NAME = "SPETS"

local PROJECT_VERSION_MINOR = 2
local PROJECT_VERSION_MAJOR = 0
local PROJECT_VERSION_YEAR = 24
local PROJECT_VERSION_REVISION = 0

local PROJECT_VERSION = PROJECT_VERSION_MAJOR .. "." .. PROJECT_VERSION_MINOR .. "-" .. PROJECT_VERSION_YEAR .. "." .. PROJECT_VERSION_REVISION

workspace (PROJECT_NAME)
	configurations { "Debug", "Release", "Final" }
	platforms { "x64", "x86" }
	location "../../"
	startproject (PROJECT_NAME)

project (PROJECT_NAME)
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	
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
	  targetname (PROJECT_NAME .. "d" .. PROJECT_VERSION .. "_Debug" )
	
	filter "configurations:Release"
      defines { "NDEBUG", "RELEASE" }
	  targetname (PROJECT_NAME .. "_p" .. PROJECT_VERSION )
	  optimize "On"
	 
	filter "configurations:Final"
      defines { "FINAL" }
	  targetname (PROJECT_NAME .. "_r" .. PROJECT_VERSION )
	  symbols "Off"
	  optimize "Full"

	filter "system:windows"
	  defines { "_WINDOWS" }
	
group "Dependencies"

include "../../libs/glfw.lua"
include "../../libs/glad.lua"
include "../../libs/glm.lua"
include "../../libs/imgui.lua"