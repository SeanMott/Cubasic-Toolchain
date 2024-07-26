#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <regex>
#include <sstream>
#include <iomanip>

namespace fs = std::filesystem;

// Structure to hold file information
struct FileInfo {
    std::string fileName;
    uint64_t fileSize;
    uint64_t fileOffset;
};

// Function to locate files in the directory and subdirectories using regex
std::vector<std::string> locateFiles(const std::string& pattern) {
    std::vector<std::string> locatedFiles;
    std::regex regexPattern(pattern);

    for (const auto& entry : fs::recursive_directory_iterator(".")) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            std::string fileName = entry.path().filename().string();

            if (std::regex_match(fileName, regexPattern)) {
                locatedFiles.push_back(filePath);
            }
        }
    }

    return locatedFiles;
}

// Function to combine files and create a header file
void combineFiles(const std::vector<std::string>& fileNames, const std::string& outputFileName, const std::string& headerFileName) {
    std::vector<FileInfo> fileInfos;
    std::ofstream outputFile(outputFileName, std::ios::binary);
    std::ofstream headerFile(headerFileName);

    uint64_t currentOffset = 0;
    const std::size_t bufferSize = 4096;
    char buffer[bufferSize];

    for (const auto& fileName : fileNames) {
        std::ifstream inputFile(fileName, std::ios::binary);
        if (!inputFile) {
            std::cerr << "Failed to open file: " << fileName << std::endl;
            continue;
        }

        inputFile.seekg(0, std::ios::end);
        uint64_t fileSize = inputFile.tellg();
        inputFile.seekg(0, std::ios::beg);

        while (inputFile) {
            inputFile.read(buffer, bufferSize);
            std::streamsize bytesRead = inputFile.gcount();
            outputFile.write(buffer, bytesRead);
        }

        FileInfo fileInfo = { fileName, fileSize, currentOffset };
        fileInfos.push_back(fileInfo);

        currentOffset += fileSize;
    }

    // Write header file with hexadecimal offsets
    for (const auto& fileInfo : fileInfos) {
        headerFile << "File: " << fileInfo.fileName
            << ", Size: " << fileInfo.fileSize
            << ", Offset: 0x" << std::hex << fileInfo.fileOffset << std::dec << std::endl;
    }
}

int main() {
    std::string pattern = R"(.*\.png$)"; // Regex pattern to match .txt files
    std::string outputFileName = "combined.bin";
    std::string headerFileName = "header.txt";

    std::vector<std::string> locatedFiles = locateFiles(pattern);
    combineFiles(locatedFiles, outputFileName, headerFileName);

    return 0;
}
