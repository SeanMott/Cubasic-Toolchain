"""
Sets up the project and gathers all the dependices and compiles the ones that are needed
"""

import subprocess
import os
from git import Repo

#get repos
SDL_GIT_REPO_LINK = "https://github.com/libsdl-org/SDL.git"
FMT_GIT_REPO_LINK = "https://github.com/fmtlib/fmt.git"
GLM_GIT_REPO_LINK = "https://github.com/g-truc/glm.git"
YAML_CPP_GIT_REPO_LINK = "https://github.com/jbeder/yaml-cpp.git"
STB_GIT_REPO_URL = "https://github.com/nothings/stb.git"

VULKAN_HEADERS_GIT_REPO_LINK = "https://github.com/KhronosGroup/Vulkan-Headers.git"
VMA_GIT_REPO_LINK = "https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator.git"
VOLK_GIT_REPO_LINK = "https://github.com/zeux/volk.git"
BOOTSTRAPPER_GIT_REPO_LINK = "https://github.com/charles-lunarg/vk-bootstrap.git"

#if the folder doesn't exist, we download it
def GetIfNotThere(URL, outputDir, branch = "main"):
    if not os.path.exists(outputDir):
        Repo.clone_from(URL, outputDir, branch = branch)
        #subprocess.run(["git", "clone", URL, outputDir],
        #shell=True)

#gets SDL 2
GetIfNotThere(SDL_GIT_REPO_LINK, "Venders/SDL", branch = "SDL2")

#builds SDL 2
subprocess.run(["cmake", "-S", "Venders/SDL", "-B", "Venders/SDL/Build"],
        shell=True)
subprocess.run(["msbuild", "Venders/SDL/Build/SDL2.sln", "-maxCpuCount:4", "/property:Configuration=Release"],
        shell=True)
subprocess.run(["msbuild", "Venders/SDL/Build/SDL2.sln", "-maxCpuCount:4", "/property:Configuration=MinSizeRel"],
        shell=True)
subprocess.run(["msbuild", "Venders/SDL/Build/SDL2.sln", "-maxCpuCount:4", "/property:Configuration=RelWithDebInfo"],
        shell=True)
           
#gets FMT
GetIfNotThere(FMT_GIT_REPO_LINK, "Venders/FMT")

#gets GLM
GetIfNotThere(GLM_GIT_REPO_LINK, "Venders/GLM")

#gets STB
GetIfNotThere(STB_GIT_REPO_URL, "Venders/STB")

#gets Vulkan headers
GetIfNotThere(VULKAN_HEADERS_GIT_REPO_LINK, "Venders/VulkanHeaders")

#gets VMA
GetIfNotThere(VMA_GIT_REPO_LINK, "Venders/VMA")

#gets Volk
GetIfNotThere(VOLK_GIT_REPO_LINK, "Venders/Volk")

#gets Bootstrapper
GetIfNotThere(BOOTSTRAPPER_GIT_REPO_LINK, "Venders/VKBootstrap")

#generate Premake file
#premakeCode = """workspace "CubasicToolchain"
"""
architecture "x64"
startproject "Cubeulator"

configurations
{
    "Debug",
    "Release",
    "Dist"
}

--the emulator for the fake console
project "Cubeulator"
location "Cubeulator"
kind "ConsoleApp"
language "C++"

targetdir (\"bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}\")
objdir (\"bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}\")


files 
{
    ---base code
    "Cubeulator/includes/**.h",
    "Cubeulator/src/**.c",
    "Cubeulator/includes/**.hpp",
    "Cubeulator/src/**.cpp",

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
    "Cubeulator/includes",

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

targetdir (\"bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}\")
objdir (\"bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}\")


files 
{
    ---base code
    "PixelCube/includes/**.h",
    "PixelCube/src/**.c",
    "PixelCube/includes/**.hpp",
    "PixelCube/src/**.cpp",

    ---imgui
}

includedirs
{
    "PixelCube/includes",

    "Venders/FMT/include",
    "Venders/GLM",
    "Venders/STB",
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

filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"

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

--compiler for generating the "ROM"s for the fake console
project "Cublic"
location "Cublic"
kind "ConsoleApp"
language "C++"

targetdir (\"bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}\")
objdir (\"bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}/%{prj.name}\")


files 
{
    ---base code
    "Cublic/includes/**.h",
    "Cublic/src/**.c",
    "Cublic/includes/**.hpp",
    "Cublic/src/**.cpp",

    ---imgui
}

includedirs
{
    "Cublic/includes",

    "Venders/FMT/include",
    "Venders/GLM"
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

filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"

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
"""

#file = open("Premake5.lua", "w")
#file.write(premakeCode)
#file.close()

#subprocess.run(["GenProject.bat"],
#        shell=True)

#performs test buillds
#subprocess.run(["msbuild", "CubasicToolchain.sln", "-maxCpuCount:4", "/property:Configuration=Debug"],
#        shell=True)
#subprocess.run(["msbuild", "CubasicToolchain.sln", "-maxCpuCount:4", "/property:Configuration=Release"],
#        shell=True)
#subprocess.run(["msbuild", "CubasicToolchain.sln", "-maxCpuCount:4", "/property:Configuration=Dist"],
#        shell=True)

#moves SDL to the right folder

print("\n\n\n------Project is all ready to go :3-------")