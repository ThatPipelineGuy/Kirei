-- Project configuration
set_project("Kirei")
set_version("0.0.1")  -- Version of your project
set_xmakever("2.9.0")  -- Minimum xmake version required

-- Metadata
set_description("Kirei: A Modern UI Framework")
set_license("MIT")
set_warnings("all", "error")
set_languages("cxx20")

-- Common build modes
add_rules("mode.debug", "mode.release")

-- Include directories
add_includedirs("include", "src")

-- Fetch glfw dependency
add_requires("glfw")

-- Target for Kirei Library (DLL)
target("Kirei")
    set_kind("shared")  -- Dynamic DLL
    set_basename("kirei")

    -- Source files
    add_files("src/core/*.cpp", "src/window/*.cpp", "src/input/*.cpp")

    -- Include directories
    add_includedirs("include", "src")

    -- Use glfw dependency
    add_packages("glfw")

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
    
    -- Source files for example project
    add_files("examples/showroom/*.cpp")
    
    -- Include directories for examples
    add_includedirs("include", "src", "examples/showroom")
    
    -- Link with Kirei DLL
    add_links("kirei")
    add_linkdirs("$(buildir)/$(plat)/$(arch)/$(mode)")
    
    -- Use glfw dependency
    add_packages("glfw")
    
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

-- Copy Kirei DLL to the output directory of showroom for runtime
after_build(function (target)
    if target:name() == "showroom" then
        os.cp("$(buildir)/$(plat)/$(arch)/$(mode)/kirei.dll", target:targetdir())
    end
end)
