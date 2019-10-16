-- Author: Szymon Jackiewicz
-- 
-- Project: Puzzle_Engine
-- File: puzzle_engine.lua
-- Date: 15/10/2019

project "puzzle_engine"
    location "%{wks.location}/puzzle_engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    nuget {
        "googletest.redist:1.8.3",
        "googletest:1.8.3"
    }
    
    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/src",
    }

    filter "configurations:Debug"
        buildoptions "/MTd"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        buildoptions "/MT"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        buildoptions "/MT"
        runtime "Release"
        optimize "On"
