#ifndef __LAYER_HPP__
#define __LAYER_HPP__

#include <iostream>
#include <numeric>
#include <iomanip>
#include <vector>
#include <random>
#include <cmath>

typedef std::vector<float> vectorf;
typedef std::vector<vectorf> matrixf;

template <size_t num_inputs, size_t num_neurons>
class Layer {
private:
    matrixf weights;
    vectorf biases;
    vectorf outputs;
    float sigmoid(float x) { return 1.0 / (1.0 + expf(-x)); }
    float sigmoid_prime(float x) { return x * (1 - x); }

public:
    Layer() {
        std::mt19937 rand(std::random_device{}());
        std::uniform_real_distribution<float> distribution(-1.0, 1.0);
        weights.resize(num_neurons, vectorf(num_inputs));
        outputs.resize(num_neurons);
        biases.resize(num_neurons);

        for (size_t i = 0; i < num_neurons; ++i) {
            for (size_t j = 0; j < num_inputs; ++j) {
                weights[i][j] = distribution(rand);
            }
            biases[i] = distribution(rand);
        }
    }

    vectorf forward(const vectorf& inputs) {
        for (size_t i = 0; i < num_neurons; ++i) {
            outputs[i] = biases[i];
            for (size_t j = 0; j < num_inputs; ++j) {
                outputs[i] += weights[i][j] * inputs[j];
            }
            outputs[i] = sigmoid(outputs[i]);
        }
        return outputs;
    }

    vectorf backward(const vectorf& d_output, const vectorf& inputs, float learning_rate) {
        vectorf d_inputs(num_inputs, 0.0f);

        for (size_t i = 0; i < num_neurons; ++i) {
            float delta = d_output[i] * sigmoid_prime(outputs[i]);
            for (size_t j = 0; j < num_inputs; ++j) {
                d_inputs[j] += weights[i][j] * delta;
                weights[i][j] -= learning_rate * delta * inputs[j];
            }
            biases[i] -= learning_rate * delta;
        }

        return d_inputs;
    }
};

#endif // __LAYER_HPP__