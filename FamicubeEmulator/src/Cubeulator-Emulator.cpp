#include "Cubeulator/Cubeulator-Emulator.h"
#include <iostream>

CubeulatorEmulator::CubeulatorEmulator() : window(nullptr), renderer(nullptr), isRunning(false) {}

CubeulatorEmulator::~CubeulatorEmulator() {
    cleanup();
}

void CubeulatorEmulator::cleanup() {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

void CubeulatorEmulator::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow("Cubeulator Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    isRunning = true;

    core = std::make_unique<CubixCoreCPU>();
    core->reset();
}

void CubeulatorEmulator::run() {
    while (isRunning) {
        // Handle events
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Render stuff here

        // Update screen
        SDL_RenderPresent(renderer);
    }
}

bool hasExtension(const std::string& filePath, const std::string& extension) {
    if (filePath.length() >= extension.length()) {
        return (0 == filePath.compare(filePath.length() - extension.length(), extension.length(), extension));
    }
    return false;
}

int main(int argc, char* argv[]) {
    CubeulatorEmulator emulator;
    emulator.initialize();

    // Check if a file path was provided (file dropped on the executable)
    if (argc > 1) {
        std::string filePath = argv[1];
        std::cout << "File dropped: " << filePath << std::endl;

        // Convert file path to lower case for case-insensitive comparison
        std::transform(filePath.begin(), filePath.end(), filePath.begin(), ::tolower);

        if (hasExtension(filePath, ".fcub")) {
            emulator.loadRom(filePath); // Load the ROM file
        }
        else if (hasExtension(filePath, ".s")) {
            emulator.loadRom(filePath); // Load the raw assembly file
        }
        else if (hasExtension(filePath, ".cubasic")) {
            std::cerr << "Warning: The file is a .cubasic file. Please compile it first." << std::endl;
        }
        else {
            std::cerr << "Error: Unsupported file type. Please provide a .fcub, .s, or .cubasic file." << std::endl;
            return 1;
        }
    }
    else {
        std::cerr << "Error: No file provided. Please drag and drop a file onto the executable." << std::endl;
        return 1;
    }

    emulator.run();

    return 0;
}

void CubeulatorEmulator::loadRom(const std::string& filePath) {
    // Load the ROM file from the specified file path
    std::cout << "Loading ROM: " << filePath << std::endl;
    RomLoaded = true;
    // Add ROM loading code here
}
