#include "parse_dataset.hpp"
#include <exception>

int main() {
    std::vector<MNISTImage> images(10000);
    //std::vector<MNISTLabel> labels(10000);

    try {
        images = load_mnist_images("../data/t10k-images.idx3-ubyte");
        //labels = load_mnist_labels("../data/t10k-labels.idx1-ubyte");
    } catch (std::runtime_error &e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    for(size_t i=0; i < 100; ++i) {
        std::cout << "Image[" << i << "]: ";
        for(size_t j=0; j < 10; ++j) {
            std::cout << static_cast<uint>(images[i].pixels[j]) << " ";
        } std::cout << std::endl;
    }

    return 0;
}