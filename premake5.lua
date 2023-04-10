workspace "Demo"
	architecture "x64"
	startproject "Demo"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "%{wks.location}/ui/vendor/glfw/include"
IncludeDir["imgui"] = "%{wks.location}/ui/vendor/imgui"

group "Core"
	include "ui"
group ""

group "Dependencies"
	include "ui/vendor/glfw"
	include "ui/vendor/imgui"
group ""

-- Clean function [1] --
newaction {
	trigger	= "clean",
	description = "Clean all generated files as such as build files",
	execute	= function ()
		print("Cleaning all...")

		-- Cleans build directories --
		os.rmdir("bin"); os.rmdir("obj")

		-- If on Linux [2], cleans makefiles --
		if package.config:sub(1,1) == "/" then
			os.remove("Makefile")
			os.remove("*.make")
			os.remove("imgui.ini")
		end

		print("Done.")
	end
}


-- References:
	-- [1]: https://stackoverflow.com/a/14425862
	-- [2]: https://stackoverflow.com/a/34858390
