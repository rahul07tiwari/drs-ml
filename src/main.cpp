#include "network.hpp"

int main() {
    Network<2, 1> xor_net({2});

    MatrixD xor_inputs = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    MatrixD xor_outputs = {{0}, {1}, {1}, {0}};

    std::cout << "Training Neural Network..." << std::endl;
    xor_net.train(xor_inputs, xor_outputs, 1000, 1.0);

    std::cout << "Testing Network:" << std::endl;
    for (const auto& input : xor_inputs) {
        auto output = xor_net.feedforward(input);
        for (auto& out : output) {
            std::cout << "Output -> " << out << std::endl;
        }
    }

    return 0;
}
