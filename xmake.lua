-- Project configuration
set_project("Kirei")
set_version("0.0.1")  -- Version of your project
set_xmakever("2.9.0")  -- Minimum xmake version required

-- Metadata
set_description("Kirei: A Modern UI Framework")
set_license("MIT")
set_warnings("all", "error")
set_languages("cxx20")
set_author("Dimitri Mitchell")
add_contributors("qtpyDev")

-- Common build modes
add_rules("mode.debug", "mode.release")

-- Include directories
add_includedirs("include", "src")

-- fetch glfw dependency
add_requires("glfw")

-- Target for Kirei Library (DLL)
target("Kirei")
    set_kind("shared")  -- Dynamic DLL
    set_basename("kirei")
    
    -- Version details
    set_version("0.0.1", {build = "%Y%m%d%H%M"})  -- Set version format and build info
    
    -- Source files
    add_files("src/**/*.cpp")  -- All .cpp files under src/
    
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

-- Target for Example Projects
target("showroom")
    set_kind("binary")  -- Build as an executable
    set_basename("showroom")
    set_group("examples")
    
    -- Version details
    set_version("1.0.0", {build = "%Y%m%d%H%M"})
    
    -- Source files for example project
    add_files("examples/showroom/*.cpp")
    
    -- Include directories for examples
    add_includedirs("include", "src", "examples/showroom")
    
    -- Link with the Kirei DLL
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

-- Copy Kirei DLL to the output directory of example1 for runtime
after_build(function (target)
    if target:name() == "example1" then
        os.cp("$(buildir)/$(plat)/$(arch)/$(mode)/kirei.dll", target:targetdir())
    end
end)
