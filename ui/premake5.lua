project "Demo"
	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"src",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.imgui}"
	}

	links {
		"glfw",
		"imgui"
	}

	filter "system:linux"
		links { "GL" }

	filter "configurations:Debug"
	  defines { "DEBUG" }
	  symbols "On"

	filter "configurations:Release"
	  defines { "NDEBUG" }
	  optimize "On"
