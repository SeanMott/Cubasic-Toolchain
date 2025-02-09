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
STB_GIT_REPO_URL = "https://github.com/nothings/stb.git"

#if the folder doesn't exist, we download it
def GetIfNotThere(URL, outputDir, branch = "master"):
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

#generate Premake file
premakeCode = """workspace "CubasicToolchain"
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
    "Cubeulator/src/**.cpp"

    ---imgui
}

includedirs
{
    "Cubeulator/includes",

    "Venders/SDL/include",
    "Venders/FMT/include",
    "Venders/GLM"
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
    defines "BTD_DEBUG"
    symbols "On"

    links
    {
        "Venders/SDL/Build/RelWithDebInfo/SDL2.lib"
    }

filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"

    links
    {
       "Venders/SDL/Build/Release/SDL2.lib"
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
       "Venders/SDL/Build/MinSizeRel/SDL2.lib"
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
    "PixelCube/src/**.cpp"

    ---imgui
}

includedirs
{
    "PixelCube/includes",

    "Venders/FMT/include",
    "Venders/GLM",
    "Venders/STB"
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
    "Cublic/src/**.cpp"

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

file = open("Premake5.lua", "w")
file.write(premakeCode)
file.close()

subprocess.run(["GenProject.bat"],
        shell=True)

#performs test buillds
subprocess.run(["msbuild", "CubasicToolchain.sln", "-maxCpuCount:4", "/property:Configuration=Debug"],
        shell=True)
subprocess.run(["msbuild", "CubasicToolchain.sln", "-maxCpuCount:4", "/property:Configuration=Release"],
        shell=True)
subprocess.run(["msbuild", "CubasicToolchain.sln", "-maxCpuCount:4", "/property:Configuration=Dist"],
        shell=True)

#moves SDL to the right folder

print("\n\n\n------Project is all ready to go :3-------")