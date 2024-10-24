#include "layer.hpp"

int main() {
    matrixf inputs = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {1.0, 1.0}};
    vectorf targets = {0.0, 1.0, 1.0, 0.0};

    Layer<2, 2> hidden_layer;
    Layer<2, 1> output_layer;

    for (int epoch=0; epoch < 10000; ++epoch) {
        for (size_t i=0; i < inputs.size(); ++i) {
            vectorf hidden_output = hidden_layer.forward(inputs[i]);
            vectorf output = output_layer.forward(hidden_output);

            vectorf error = { output[0] - targets[i] };

            vectorf d_hidden = output_layer.backward(error, hidden_output, 0.1);
            hidden_layer.backward(d_hidden, inputs[i], 0.1);

            std::cout << "Epoch: " << epoch + 1
                      << ", Input: {" << inputs[i][0] << ", " << inputs[i][1] << "}"
                      << ", Target: " << targets[i]
                      << ", Output: " << output[0]
                      << ", Error: " << error[0]
                      << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}