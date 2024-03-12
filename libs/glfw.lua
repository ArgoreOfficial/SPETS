project "GLFW"
	kind "StaticLib"
	language "C"

	location "../build"
	targetdir "../bin"
	objdir "../bin/obj/"
	
	includedirs { "../libs/glfw/include/" }

	files
	{
--		"../libs/glfw/include/GLFW/glfw3.h",
--		"../libs/glfw/include/GLFW/glfw3native.h",
		"../libs/glfw/src/glfw_config.h",
		"../libs/glfw/src/context.c",
		"../libs/glfw/src/init.c",
		"../libs/glfw/src/input.c",
		"../libs/glfw/src/monitor.c",
		"../libs/glfw/src/vulkan.c",
		"../libs/glfw/src/window.c",
		"../libs/glfw/src/platform.c",
		"../libs/glfw/src/null_init.c",
		"../libs/glfw/src/null_monitor.c",
		"../libs/glfw/src/null_window.c",
		"../libs/glfw/src/null_joystick.c"
	}
    
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		files
		{
			"../libs/glfw/src/x11_init.c",
			"../libs/glfw/src/x11_monitor.c",
			"../libs/glfw/src/x11_window.c",
			"../libs/glfw/src/xkb_unicode.c",
			"../libs/glfw/src/posix_time.c",
			"../libs/glfw/src/posix_thread.c",
			"../libs/glfw/src/glx_context.c",
			"../libs/glfw/src/egl_context.c",
			"../libs/glfw/src/osmesa_context.c",
			"../libs/glfw/src/linux_joystick.c",
			"../libs/glfw/src/posix_module.c",
			"../libs/glfw/src/posix_poll.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"../libs/glfw/src/win32_init.c",
			"../libs/glfw/src/win32_joystick.c",
			"../libs/glfw/src/win32_monitor.c",
			"../libs/glfw/src/win32_time.c",
			"../libs/glfw/src/win32_thread.c",
			"../libs/glfw/src/win32_window.c",
			"../libs/glfw/src/wgl_context.c",
			"../libs/glfw/src/egl_context.c",
			"../libs/glfw/src/osmesa_context.c",
			"../libs/glfw/src/win32_module.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"