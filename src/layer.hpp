#pragma once

#include <time.h>
#include <vector>
#include <random>
#include <iostream>

#define SIGMOID_ACTIVATION
#include "activation.hpp"

typedef std::vector<double> VectorD;
typedef std::vector<VectorD> MatrixD;

class Layer {
private:
    VectorD biases;
    VectorD inputs;
    MatrixD weights;
    VectorD outputs;
    const size_t num_inputs;
    const size_t num_neurons;

public:
    Layer(const size_t& __num_inputs, const size_t& __num_neurons)
    :num_inputs(__num_inputs), num_neurons(__num_neurons)
    {

        std::mt19937 rand(std::random_device{}());
        std::uniform_real_distribution<double> dist(-1.0, 1.0);
        weights.resize(num_neurons, VectorD(num_inputs));
        inputs.resize(num_inputs, 0);
        outputs.resize(num_neurons);
        biases.resize(num_neurons);

        for (size_t i = 0; i < num_neurons; ++i) {
            for (size_t j = 0; j < num_inputs; ++j) {
                weights[i][j] = dist(rand);
            }
            biases[i] = dist(rand);
        }
    }

    VectorD forward(const VectorD& _inputs) 
    {
        inputs = _inputs;
        outputs.resize(num_neurons, 0.0);
        for (size_t i = 0; i < num_neurons; ++i) {
            double activation_input = biases[i];
            for (size_t j = 0; j < num_inputs; ++j) {
                activation_input += weights[i][j] * inputs[j];
            }
            outputs[i] = sigmoid(activation_input);
        }
        return outputs;
    }

    VectorD backward(const VectorD& d_outputs, const double& learning_rate)
    {
        VectorD d_inputs(num_inputs, 0.0);
        for (size_t i = 0; i < num_neurons; ++i) {
            const double delta = d_outputs[i] * sigmoid_prime(outputs[i]);
            for (size_t j = 0; j < num_inputs; ++j) {
                d_inputs[j] += weights[i][j] * delta;
                weights[i][j] += learning_rate * delta * inputs[j];
            }
            biases[i] += learning_rate * delta;
        }
        return d_inputs;
    }
};