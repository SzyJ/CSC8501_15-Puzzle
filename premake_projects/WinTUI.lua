-- Author: Szymon Jackiewicz
-- 
-- Project: Puzzle_Engine
-- File: WinTUI.lua
-- Date: 18/10/2019

project "googletest"
    location "%{wks.location}/3rd_party/googletest"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "%{prj.location}/googletest/include",
        "%{prj.location}/googletest",
    }

    files {
        "%{prj.location}/googletest/include/**.h",
        "%{prj.location}/googletest/src/**.cc"
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
