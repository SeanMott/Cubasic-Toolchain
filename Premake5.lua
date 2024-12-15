workspace "CubasicToolchain"
architecture "x64"
startproject "Cubasic"

configurations
{
    "Debug",
    "Release",
    "Dist"
}

--fmt vendor
VENDER_INCLUDE_FMT = "Venders/FMT/includes"

--library that defines the Cubasic Language and parsing

--library that defines the Cubix Core ASM for parsing

--compiler for turing Cubasic to Cubix Core ASM
project "Cubasic"
location "Cubasic"
kind "ConsoleApp"
language "C++"

targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")
objdir ("bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")


files 
{
    ---base code
    "Cubasic/includes/**.h",
    "Cubasic/src/**.c",
    "Cubasic/includes/**.hpp",
    "Cubasic/src/**.cpp"
}

includedirs
{
    "Cubasic/includes",

    VENDER_INCLUDE_FMT,
}

defines
{
   
}

flags
{
    "NoRuntimeChecks",
    "MultiProcessorCompile"
}

buildoptions { "/utf-8" } --used for fmt

--platforms
filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "Window_Build",
        "Desktop_Build"
    }

filter "system:linux"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "Linux_Build",
        "Desktop_Build"
    }

    filter "system:mac"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "MacOS_Build",
        "Desktop_Build"
    }

--configs
filter "configurations:Debug"
    defines "CUBE_DEBUG"
    symbols "On"

    links
    {
       
    }

filter "configurations:Release"
    defines "CUBE_RELEASE"
    optimize "On"

    links
    {
      
    }

filter "configurations:Dist"
    defines "CUBE_DIST"
    optimize "On"

    defines
    {
        "NDEBUG"
    }

    flags
    {
       "LinkTimeOptimization"
    }

    links
    {
     
    }

--Cubix Core Emulator
project "CubixCore"
location "CubixCore"
kind "ConsoleApp"
language "C++"

targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")
objdir ("bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")


files 
{
    ---base code
    "CubixCore/includes/**.h",
    "CubixCore/src/**.c",
    "CubixCore/includes/**.hpp",
    "CubixCore/src/**.cpp"
}

includedirs
{
    "CubixCore/includes",

    VENDER_INCLUDE_FMT,
}

defines
{
    "GLM_FORCE_RADIANS",
    "GLM_FORCE_DEPTH_ZERO_TO_ONE",
    "GLM_ENABLE_EXPERIMENTAL"
}

flags
{
    "NoRuntimeChecks",
    "MultiProcessorCompile"
}

buildoptions { "/utf-8" } --used for fmt

--platforms
filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "Window_Build",
        "Desktop_Build"
    }

filter "system:linux"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "Linux_Build",
        "Desktop_Build"
    }

    filter "system:mac"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "MacOS_Build",
        "Desktop_Build"
    }

--configs
filter "configurations:Debug"
    defines "CUBE_DEBUG"
    symbols "On"

    links
    {
       -- "Venders/SDL/Build/RelWithDebInfo/SDL2.lib"
    }

filter "configurations:Release"
    defines "CUBE_RELEASE"
    optimize "On"

    links
    {
       --"Venders/SDL/Build/Release/SDL2.lib"
    }

filter "configurations:Dist"
    defines "CUBE_DIST"
    optimize "On"

    defines
    {
        "NDEBUG"
    }

    flags
    {
       "LinkTimeOptimization"
    }

    links
    {
     --  "Venders/SDL/Build/MinSizeRel/SDL2.lib"
    }