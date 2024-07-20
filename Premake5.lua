workspace "CubasicToolchain"
architecture "x64"
startproject "FamicubeEmulator"

configurations
{
    "Debug",
    "Release",
    "Dist"
}

--the emulator for the fake console
project "Famicube-Emulator"
location "FamicubeEmulator"
kind "ConsoleApp"
language "C++"

targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")
objdir ("bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")


files 
{
    ---base code
    "FamicubeEmulator/includes/**.h",
    "FamicubeEmulator/src/**.c",
    "FamicubeEmulator/includes/**.hpp",
    "FamicubeEmulator/src/**.cpp",

    --volk
    "Venders/Volk/volk.c",
    "Venders/Volk/volk.h",

    ---vulkan bootstrapper
    "Venders/VKBootstrap/src/**.cpp",
    "Venders/VKBootstrap/src/**.h"

    ---imgui
}

includedirs
{
    "FamicubeEmulator/includes",

    "Venders/SDL/include",
    "Venders/FMT/include",
    "Venders/GLM",

    "Venders/VKBootstrap/src",
    "Venders/VMA/include",
    "Venders/Volk",
    "Venders/VulkanHeaders/include"
}

links
{
    
}

defines
{
    "GLM_FORCE_RADIANS",
    "GLM_FORCE_DEPTH_ZERO_TO_ONE",
    "GLM_ENABLE_EXPERIMENTAL",
    "VK_NO_PROTOTYPES"
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
        "Desktop_Build",
        "VK_USE_PLATFORM_WIN32_KHR"
    }

filter "system:linux"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "Linux_Build",
        "Desktop_Build",
        "VK_USE_PLATFORM_XLIB_KHR"
    }

    filter "system:mac"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "MacOS_Build",
        "Desktop_Build",
        "VK_USE_PLATFORM_MACOS_MVK"
    }

--configs
filter "configurations:Debug"
    defines "BTD_DEBUG"
    symbols "On"

    links
    {
        "Venders/SDL/Build/RelWithDebInfo/SDL3.lib"
    }

filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"

    flags
    {
        
    }

    links
    {
       "Venders/SDL/Build/Release/SDL3.lib"
    }

filter "configurations:Dist"
    defines "BTD_DIST"
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
       "Venders/SDL/Build/MinSizeRel/SDL3.lib"
    }

--tool to map sprite pixel data to the RGBA values supported by the fake console
project "PixelCube"
location "PixelCube"
kind "ConsoleApp"
language "C++"

targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")
objdir ("bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")


files 
{
    ---base code
    "PixelCube/includes/**.h",
    "PixelCube/src/**.c",
    "PixelCube/includes/**.hpp",
    "PixelCube/src/**.cpp",

    --volk
    --"Venders/Volk/volk.c",
    --"Venders/Volk/volk.h",

    ---vulkan bootstrapper
    --"Venders/VKBootstrap/src/**.cpp",
    --"Venders/VKBootstrap/src/**.h"

    ---imgui
}

includedirs
{
    "PixelCube/includes",

    --"Venders/SDL/include",
    "Venders/FMT/include",
    "Venders/GLM",
    "Venders/STB",

    --"Venders/VKBootstrap/src",
    --"Venders/VMA/include",
    --"Venders/Volk",
    --"Venders/VulkanHeaders/include"
}

links
{
    
}

defines
{
    "GLM_FORCE_RADIANS",
    "GLM_FORCE_DEPTH_ZERO_TO_ONE",
    "GLM_ENABLE_EXPERIMENTAL",
    "VK_NO_PROTOTYPES"
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
        "Desktop_Build",
        "VK_USE_PLATFORM_WIN32_KHR"
    }

filter "system:linux"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "Linux_Build",
        "Desktop_Build",
        "VK_USE_PLATFORM_XLIB_KHR"
    }

    filter "system:mac"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "MacOS_Build",
        "Desktop_Build",
        "VK_USE_PLATFORM_MACOS_MVK"
    }

--configs
filter "configurations:Debug"
    defines "BTD_DEBUG"
    symbols "On"

    links
    {
        --"Venders/SDL/Build/RelWithDebInfo/SDL3.lib"
    }

filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"

    flags
    {
        
    }

    links
    {
       --"Venders/SDL/Build/Release/SDL3.lib"
    }

filter "configurations:Dist"
    defines "BTD_DIST"
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
       --"Venders/SDL/Build/MinSizeRel/SDL3.lib"
    }

--compiler for generating the "ROM"s for the fake console
project "Cublic"
location "Cublic"
kind "ConsoleApp"
language "C++"

targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")
objdir ("bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}")


files 
{
    ---base code
    "Cublic/includes/**.h",
    "Cublic/src/**.c",
    "Cublic/includes/**.hpp",
    "Cublic/src/**.cpp",

    --volk
    --"Venders/Volk/volk.c",
    --"Venders/Volk/volk.h",

    ---vulkan bootstrapper
    --"Venders/VKBootstrap/src/**.cpp",
    --"Venders/VKBootstrap/src/**.h"

    ---imgui
}

includedirs
{
    "Cublic/includes",

    --"Venders/SDL/include",
    "Venders/FMT/include",
    "Venders/GLM"

    --"Venders/VKBootstrap/src",
    --"Venders/VMA/include",
    --"Venders/Volk",
    --"Venders/VulkanHeaders/include"
}

links
{
    
}

defines
{
    "GLM_FORCE_RADIANS",
    "GLM_FORCE_DEPTH_ZERO_TO_ONE",
    "GLM_ENABLE_EXPERIMENTAL",
    "VK_NO_PROTOTYPES"
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
        "Desktop_Build",
        "VK_USE_PLATFORM_WIN32_KHR"
    }

filter "system:linux"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "Linux_Build",
        "Desktop_Build",
        "VK_USE_PLATFORM_XLIB_KHR"
    }

    filter "system:mac"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "MacOS_Build",
        "Desktop_Build",
        "VK_USE_PLATFORM_MACOS_MVK"
    }

--configs
filter "configurations:Debug"
    defines "BTD_DEBUG"
    symbols "On"

    links
    {
        --"Venders/SDL/Build/RelWithDebInfo/SDL3.lib"
    }

filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"

    flags
    {
        
    }

    links
    {
       --"Venders/SDL/Build/Release/SDL3.lib"
    }

filter "configurations:Dist"
    defines "BTD_DIST"
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
       --"Venders/SDL/Build/MinSizeRel/SDL3.lib"
    }
