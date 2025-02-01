include "../Common.lua"

--defines a common lib
CUBECOMMON_DIR_INCLUDE = "CubeCommon/includes"
CUBECOMMON_LINK = "CubeCommon"
project "CubeCommon"
kind "StaticLib"
language "C++"

targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")
objdir ("bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")


files 
{
    ---base code
    "includes/**.h",
    "src/**.c",
    "includes/**.hpp",
    "src/**.cpp"
}

includedirs
{
    "includes",

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