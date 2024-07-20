#ifndef CUBIXCORECPU_H
#define CUBIXCORECPU_H

#include <memory>
#include <array>
#include <stdexcept>
#include <iostream>
#include "MemoryManager.h" // Include MemoryManager header

class CubixCoreCPU {
public:
    CubixCoreCPU();

    void reset(); // Reset all registers to initial state

    // Methods to access and modify registers
    unsigned char getGeneralRegister(size_t index) const;
    void setGeneralRegister(size_t index, unsigned char value);

    unsigned short getPointerRegister(size_t index) const;
    void setPointerRegister(size_t index, unsigned short value);

    unsigned short getProgramCounter() const;
    void setProgramCounter(unsigned short value);

    unsigned char getStackPointer() const;
    void setStackPointer(unsigned char value);

    unsigned char getStatusRegister() const;
    void setStatusRegister(unsigned char value);

private:
    std::array<unsigned char, 8> generalRegisters;
    std::array<unsigned short, 2> pointerRegisters;
    unsigned short programCounter;
    unsigned char stackPointer;
    unsigned char statusRegister;

    std::unique_ptr<MemoryManager> memoryManager;
};

#endif // CUBIXCORECPU_H
