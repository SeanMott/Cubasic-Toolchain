#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <memory>
#include <stdexcept>
#include <algorithm>

class MemoryManager {
public:
    MemoryManager(size_t size);
    ~MemoryManager();

    unsigned char read(size_t address) const;
    void write(size_t address, unsigned char value);

private:
    std::unique_ptr<unsigned char[]> memory;
    size_t size;
};

#endif // MEMORYMANAGER_H
