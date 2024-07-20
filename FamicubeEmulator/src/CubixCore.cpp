#include "CubixCore.h"

CubixCoreCPU::CubixCoreCPU() : programCounter(0), stackPointer(0), statusRegister(0), memoryManager(std::make_unique<MemoryManager>(65536)) {
    generalRegisters.fill(0);
    pointerRegisters.fill(0);
}

void CubixCoreCPU::reset() {
    generalRegisters.fill(0);
    pointerRegisters.fill(0);
    programCounter = 0;
    stackPointer = 0;
    statusRegister = 0;
}

unsigned char CubixCoreCPU::getGeneralRegister(size_t index) const {
    if (index >= generalRegisters.size()) throw std::out_of_range("Invalid register index");
    return generalRegisters[index];
}

void CubixCoreCPU::setGeneralRegister(size_t index, unsigned char value) {
    if (index >= generalRegisters.size()) throw std::out_of_range("Invalid register index");
    generalRegisters[index] = value;
}

unsigned short CubixCoreCPU::getPointerRegister(size_t index) const {
    if (index >= pointerRegisters.size()) throw std::out_of_range("Invalid register index");
    return pointerRegisters[index];
}

void CubixCoreCPU::setPointerRegister(size_t index, unsigned short value) {
    if (index >= pointerRegisters.size()) throw std::out_of_range("Invalid register index");
    pointerRegisters[index] = value;
}

unsigned short CubixCoreCPU::getProgramCounter() const {
    return programCounter;
}

void CubixCoreCPU::setProgramCounter(unsigned short value) {
    programCounter = value;
}

unsigned char CubixCoreCPU::getStackPointer() const {
    return stackPointer;
}

void CubixCoreCPU::setStackPointer(unsigned char value) {
    stackPointer = value;
}

unsigned char CubixCoreCPU::getStatusRegister() const {
    return statusRegister;
}

void CubixCoreCPU::setStatusRegister(unsigned char value) {
    statusRegister = value;
}
