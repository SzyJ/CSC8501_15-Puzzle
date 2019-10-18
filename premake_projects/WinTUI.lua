-- Author: Szymon Jackiewicz
-- 
-- Project: Puzzle_Engine
-- File: WinTUI.lua
-- Date: 18/10/2019

project "WinTUI"
    location "%{wks.location}/3rd_party/WinTUI"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs {
        "%{prj.location}/WinTUI/include",
        "%{prj.location}/WinTUI/build"
    }

    files {
        "%{prj.location}/WinTUI/include/**.h",
        "%{prj.location}/WinTUI/build/**.cpp"
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
