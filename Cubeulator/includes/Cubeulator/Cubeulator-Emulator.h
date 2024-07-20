#ifndef Cubeulator_EMULATOR_H
#define Cubeulator_EMULATOR_H

#if defined(_WIN32)
#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "CubixCore.h"

class CubeulatorEmulator {
public:
    bool RomLoaded = false;

    CubeulatorEmulator();
    ~CubeulatorEmulator();

    void cleanup();

    void initialize();
    void run();
    void shutdown();

    void loadRom(const std::string& filePath);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::unique_ptr<CubixCoreCPU> core;

    bool isRunning;
};

#endif // Cubeulator_EMULATOR_H
