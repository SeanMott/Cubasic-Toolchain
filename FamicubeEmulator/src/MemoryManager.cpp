#include "Cubeulator/MemoryManager.h"

// Implementation of MemoryManager methods

MemoryManager::MemoryManager(size_t size) : size(size), memory(std::make_unique<unsigned char[]>(size)) {
    std::fill(memory.get(), memory.get() + size, 0);
}

MemoryManager::~MemoryManager() {}

unsigned char MemoryManager::read(size_t address) const {
    if (address >= size) throw std::out_of_range("Invalid memory address");
    return memory[address];
}

void MemoryManager::write(size_t address, unsigned char value) {
    if (address >= size) throw std::out_of_range("Invalid memory address");
    memory[address] = value;
}
