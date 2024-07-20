/*
Pixel Cube, a dev tool for mapping sprites to pixel formats supported by the fake console
*/

#include <PixelCube/Palette.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>s

#define FMT_HEADER_ONLY
#include <fmt/color.h>
#include <fmt/core.h>

#include <string>
#include <sstream>
#include <iomanip>

//finds the closet color
static inline glm::vec3 findClosestColor(const glm::vec3& color)
{
    int minDistanceSquared = std::numeric_limits<int>::max();
    glm::vec3 closestColor = color;

    for (const auto& paletteColor : FamiCubePalette) {
        glm::vec3 delta = color - paletteColor;
        int distanceSquared = (delta.r * delta.r + delta.g * delta.g + delta.b * delta.b);

        if (distanceSquared < minDistanceSquared)
        {
            minDistanceSquared = distanceSquared;
            closestColor = paletteColor;
        }
    }

    return closestColor;
}

//process a pixel
static inline void processPixel(unsigned char* pixel, int channels)
{
    glm::vec3 currentColor(pixel[0], pixel[1], pixel[2]);
    glm::vec3 newColor = findClosestColor(currentColor);
    pixel[0] = static_cast<unsigned char>(newColor.r);
    pixel[1] = static_cast<unsigned char>(newColor.g);
    pixel[2] = static_cast<unsigned char>(newColor.b);
}

//writes a image to disc
static inline bool writeImage(const std::string& outputPath, const unsigned char* img, int width, int height, int channels)
{
    if (!stbi_write_png(outputPath.c_str(), width, height, channels, img, width * channels))
    {
        fmt::print(fmt::fg(fmt::color::red), "PIXEL CUBE ERROR: Write Image || Failed to write a image to ");
        fmt::print(fmt::fg(fmt::color::blue), " \"{}\"\n", outputPath);
        return false;
    }

    return true;
}

//process the image
bool processImage(const std::string& inputPath, const std::string& outputPath)
{
    //load image
    int width, height, channels;
    unsigned char* img = stbi_load(inputPath.c_str(), &width, &height, &channels, 0);

    //failed to load
    if (!img)
    {
        fmt::print(fmt::fg(fmt::color::red), "PIXEL CUBE ERROR: Process Image || Failed to process image loaded from ");
        fmt::print(fmt::fg(fmt::color::blue), " \"{}\". ", outputPath);
        fmt::print(fmt::fg(fmt::color::purple), "Make sure the path is actually a path.\n");
        return false;
    }

    // Process each pixel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char* pixel = img + (y * width + x) * channels;
            processPixel(pixel, channels);
        }
    }

    // Write the processed image to file
    writeImage(outputPath, img, width, height, channels);

    // Free the image data
    stbi_image_free(img);

    return true;
}

//turns a image into a hex string
std::string imageToHexString(const unsigned char* img, int width, int height, int channels)
{
    std::stringstream ss;

    // Iterate over each pixel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Pointer to the current pixel
            const unsigned char* pixel = img + (y * width + x) * channels;

            // Convert the RGB values to a hexadecimal string
            for (int c = 0; c < 3; ++c) { // Assuming channels includes RGB, ignoring alpha if present
                ss << std::setfill('0') << std::setw(2) << std::hex << (int)pixel[c];
            }

            // If at the end of a line of 128 pixels, insert a newline character
            if ((x + 1) % 128 == 0) {
                ss << '\n';
            }
        }
    }

    return ss.str();
}

//entry point
int main(int argc, char* argv[])
{
    if (argc < 2) {
        fmt::print("Usage: PixelCube.exe ");
        fmt::print(fmt::fg(fmt::color::purple), " <input_image_path> [--to-hex | output_image_path]\n");;
        return 1;
    }

    std::string inputImagePath = argv[1];
    std::string outputImagePath;
    bool toHex = false;

    if (argc == 3) {
        std::string arg = argv[2];
        if (arg == "--to-hex") {
            toHex = true;
        }
        else {
            outputImagePath = arg;
        }
    }
    else {
        // Generate output path by appending "_converted" to the input file name
        size_t dotIndex = inputImagePath.find_last_of(".");
        if (dotIndex != std::string::npos) {
            outputImagePath = inputImagePath.substr(0, dotIndex) + "_converted" + inputImagePath.substr(dotIndex);
        }
        else {
            outputImagePath = inputImagePath + "_converted";
        }
    }

    // Load the image
    int width, height, channels;
    unsigned char* img = stbi_load(inputImagePath.c_str(), &width, &height, &channels, 0);

    if (!img) {
        fmt::print(fmt::fg(fmt::color::red), "PIXEL CUBE ERROR: Main || Failed to load image ");
        fmt::print(fmt::fg(fmt::color::blue), " \"{}\". ", inputImagePath);
        stbi_image_free(img);
        return 1;
    }

    if (toHex) {
        // Convert image to hex string
        std::string hexString = imageToHexString(img, width, height, channels);
        fmt::print("Image Hex: {}\n", hexString);
    }
    else {
        // Process the image normally
        processImage(inputImagePath, outputImagePath);
    }

    stbi_image_free(img);
    return 0;
}