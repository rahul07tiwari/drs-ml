#ifndef __PARSE_DATASET__
#define __PARSE_DATASET__

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

struct MNISTImage { std::vector<uint8_t> pixels; };
struct MNISTLabel { uint8_t label; };

uint32_t byteswap32(uint32_t value) {
    return ((value & 0x000000FF) << 24) | ((value & 0x0000FF00) << 8) |
            ((value & 0x00FF0000) >> 8) | ((value & 0xFF000000) >> 24);
}

std::vector<float> normalize(const MNISTImage &image) {
    std::vector<float> normalized(image.pixels.size());
    for (size_t i = 0; i < image.pixels.size(); ++i) {
        normalized[i] = image.pixels[i] / 255.0f;
    }
    return normalized;
}

std::vector<MNISTImage> load_mnist_images(const std::string &filename) {
    std::ifstream file(filename, std::ios_base::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    uint32_t magic_num = 0, num_of_img = 0, rows = 0, cols = 0;

    file.read(reinterpret_cast<char *>(&magic_num), 4);
    file.read(reinterpret_cast<char *>(&num_of_img), 4);
    file.read(reinterpret_cast<char *>(&rows), 4);
    file.read(reinterpret_cast<char *>(&cols), 4);

    if (byteswap32(magic_num) != 2051) {
        throw std::runtime_error("Invalid magic number in MNIST image file.");
    }

    num_of_img = byteswap32(num_of_img);
    rows = byteswap32(rows);
    cols = byteswap32(cols);

    std::vector<MNISTImage> images(num_of_img);
    for (size_t i=0; i < num_of_img; ++i) {
        MNISTImage image;
        image.pixels.resize(rows * cols);
        file.read(reinterpret_cast<char *>(image.pixels.data()), rows * cols);
        images[i] = image;
    }

    file.close();
    return images;
}

std::vector<MNISTLabel> load_mnist_labels(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
     
    uint32_t magic_num = 0, num_of_labels = 0;

    file.read(reinterpret_cast<char *>(&magic_num), 4);
    file.read(reinterpret_cast<char *>(&num_of_labels), 4);

    if (byteswap32(magic_num) != 2049) {
        throw std::runtime_error("Invalid magic number in MNIST label file.");
    }

    num_of_labels = byteswap32(num_of_labels);
    std::vector<MNISTLabel> labels(num_of_labels);
    file.read(reinterpret_cast<char *>(labels.data()), num_of_labels);

    file.close();
    return labels;
}

#endif // __PARSE_DATASET__