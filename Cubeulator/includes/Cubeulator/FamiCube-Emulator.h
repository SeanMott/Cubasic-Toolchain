#ifndef FAMICUBE_EMULATOR_H
#define FAMICUBE_EMULATOR_H

#if defined(_WIN32)
#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "CubixCore.h"

class FamicubeEmulator {
public:
    bool RomLoaded = false;

    FamicubeEmulator();
    ~FamicubeEmulator();

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

#endif // FAMICUBE_EMULATOR_H
