-- Author: Szymon Jackiewicz
-- 
-- Project: Puzzle_Engine
-- File: puzzle_engine_test.lua
-- Date: 15/10/2019

project "puzzle_engine_test"
    location "%{wks.location}/puzzle_engine_test"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/test/**.h",
        "%{prj.location}/test/**.cpp"
    }

    includedirs {
        "%{wks.location}/puzzle_engine/src",
        "%{wks.location}/3rd_party/googletest/googletest/include"
    }

    links {
        "puzzle_engine",
        "googletest"
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
