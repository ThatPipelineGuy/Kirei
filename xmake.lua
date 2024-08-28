-- Project configuration
set_project("Kirei")
set_version("0.0.1")
set_xmakever("2.9.0")

-- Metadata
set_description("Kirei: A Modern UI Framework")
set_license("MIT")
set_warnings("all", "error")
set_languages("cxx20")

-- Common build modes
add_rules("mode.debug", "mode.release")

-- Include directories
add_includedirs("include", "src")

-- Fetch dependencies
add_requires("glfw")
add_requires("glad")

-- Target for Kirei Library (Static Library)
target("Kirei")
    set_kind("static")
    set_basename("kirei")
    
    -- Set output directory for kirei.lib
    set_targetdir("$(buildir)/$(plat)/$(arch)/$(mode)")

    -- Source files
    add_files("src/core/*.cpp", "src/window/*.cpp", "src/input/*.cpp", "src/renderer/*.cpp")

    -- Include directories
    add_includedirs("include", "src")

    -- Use dependencies
    add_packages("glfw", "glad")

    -- Platform-specific configurations
    if is_plat("windows") then
        add_defines("GLFW_INCLUDE_NONE")
    end

    -- Debug build configurations
    if is_mode("debug") then
        set_symbols("debug")
        add_defines("DEBUG")
        set_optimize("none")
    end

    -- Release build configurations
    if is_mode("release") then
        set_optimize("fastest")
        set_strip("all")
    end

-- Target for Showroom Example Project
target("showroom")
    set_kind("binary")
    set_basename("showroom")
    set_group("examples")
    
    -- Set dependency on Kirei library
    add_deps("Kirei")

    -- Source files for example project
    add_files("examples/showroom/*.cpp")
    
    -- Include directories for examples
    add_includedirs("include", "src", "examples/showroom")
    
    -- Link with Kirei static library
    add_links("kirei")
    
    -- Explicitly set the link directory to where Kirei's .lib file is generated
    add_linkdirs("$(buildir)/$(plat)/$(arch)/$(mode)")

    -- Use dependencies
    add_packages("glfw", "glad")

    -- Debug build configurations
    if is_mode("debug") then
        set_symbols("debug")
        add_defines("DEBUG")
        set_optimize("none")
    end

    -- Release build configurations
    if is_mode("release") then
        set_optimize("fastest")
        set_strip("all")
    end