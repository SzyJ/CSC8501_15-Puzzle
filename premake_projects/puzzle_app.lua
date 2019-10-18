-- Author: Szymon Jackiewicz
-- 
-- Project: Puzzle_Engine
-- File: puzzle_app.lua
-- Date: 15/10/2019

project "puzzle_app"
    location "%{wks.location}/puzzle_app"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{wks.location}/puzzle_engine/src",
        "%{wks.location}/3rd_party/WinTUI/WinTUI/include"
    }

    links {
        "WinTUI",
        "puzzle_engine"
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
