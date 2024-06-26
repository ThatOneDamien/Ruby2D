project "RubyEditor"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/int/" .. outdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/third_party",
		"%{wks.location}/Ruby/src",
		"%{wks.location}/Ruby/Dependencies/glm",
        "%{wks.location}/Ruby/Dependencies/entt/include"
	}

	filter "system:windows"
		kind "WindowedApp"
		systemversion "latest"
        entrypoint "WinMainCRTStartup"
		links "Ruby"

	filter "system:linux"
	    kind "ConsoleApp"
		links 
		{
			"Ruby", 
			"glad", 
			"GLFW", 
			"ImGui", 
			"msdf-atlas-gen", 
			"msdfgen", 
			"FreeType", 
			"SoloudStatic"
		}
		disablewarnings "format-security"
	    

	filter "configurations:Debug"
		defines "RB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RB_RELEASE"
		runtime "Release"
		optimize "on"
