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