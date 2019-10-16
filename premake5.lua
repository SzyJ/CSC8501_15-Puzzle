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

    -- Logic Libraries --
    include "premake_projects/puzzle_engine.lua"

    -- Main Project --
    -- Requires: puzzle_engine
    include "premake_projects/sandbox.lua"
