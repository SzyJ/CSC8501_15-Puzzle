-- Author: Szymon Jackiewicz
-- 
-- Project: Puzzle_Engine
-- File: premake5.lua
-- Date: 18/10/2019

workspace "Puzzle_Engine"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "puzzle_app"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


    -- Logic Libraries --
    include "premake_projects/puzzle_engine.lua"
    include "premake_projects/WinTUI.lua"

    -- Main Project --
    -- Requires: puzzle_engine, WinTUI
    include "premake_projects/puzzle_app.lua"

    -- Testing --
    include "premake_projects/googletest.lua"
    include "premake_projects/puzzle_engine_test.lua"
