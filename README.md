# Cubasic-Toolchain
A toolchain for using Cubasic and FCMAKE to output PASM

# Building

## Windows

### Step 1: Deps
- Python 3, Visual Studio 2022 or beyond, and CMake is required

- MsBuild must be in the System Path. It can be found after installing Visual Studio, roughly at `C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin`

### Step 2: Build/Gen

- run `ProjectSetup.py` in the root of the folder (ie where this README is)

- wait for `ProjectSetup` to download everything, build SDL 3, generate the project, perform a test build and move SDL to the bin folder.

- open Visual Studio and build

- go into `Venders/SDL/Build` and pick a flavor of SDL by grabbing the DLL in `Release`, `RelWithDebInfo`, or `MinSizeRel`. Throw it next to `FamicubeEmulator.exe` build in `bin/BuildTypeOfYourChoiceHere/Famicube-Emulator`

- Enjoy :3


## Credits

-------Insert Jinxy Stuff here---------