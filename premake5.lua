-- Author: Szymon Jackiewicz
-- 
-- Project: Puzzle_Engine
-- File: premake5.lua
-- Date: 15/10/2019

workspace "Puzzle_Engine"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "sandbox"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    -- Dependencies
    extincludes = {}
    extincludes["puzzle_engine"]  = "%{wks.location}/puzzle_engine/src"
    extincludes["googletest"] = "%{wks.location}/3rd_party/googletest/googletest/include"

    -- Logic Libraries --
    include "premake_projects/puzzle_engine.lua"

    -- Main Project --
    -- Requires: puzzle_engine
    include "premake_projects/sandbox.lua"

    -- Testing --
    include "premake_projects/googletest.lua"
    include "premake_projects/puzzle_engine_test.lua"

