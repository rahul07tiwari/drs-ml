#pragma once
#include "layer.hpp"

#include <iostream>
#include <stdexcept>

typedef std::vector<Layer> Layers;

template<size_t input_size, size_t output_size>
class Network {

public:
    Network(const std::vector<unsigned>& topology)
    :output_layer(topology.empty() ? 0 : topology.back(), output_size)
    {
        if (topology.empty()) {
            throw std::invalid_argument("Topology must have at least one hidden layer.");
        }

        hidden_layers.emplace_back(input_size, topology.front());

        for (size_t i = 1; i < topology.size() - 1; ++i) {
            hidden_layers.emplace_back(topology[i - 1], topology[i]);
        }
    }

    VectorD feedforward(const VectorD& inputs)
    {
        VectorD hidden_output = hidden_layers.front().forward(inputs);
        for (size_t i = 1; i < hidden_layers.size(); ++i) {
            hidden_output = hidden_layers[i].forward(hidden_output);
        }
        return output_layer.forward(hidden_output);
    }

    void backpropagate(const VectorD& output_errors, const double& learning_rate) {
        VectorD prevl_errors = output_layer.backward(output_errors,learning_rate);
        for (int i = hidden_layers.size() - 1; i >= 0; --i) {
            prevl_errors = hidden_layers[i].backward(prevl_errors, learning_rate);
        }
    }

    void train(const MatrixD& inputs, const MatrixD& targets,
               const unsigned& epochs, const double& learning_rate = 0.1)
    {
        if (inputs.size() != targets.size()) {
            throw std::invalid_argument("The number of inputs must match the number of targets");
        }

        for (unsigned epoch = 0; epoch < epochs; ++epoch) {
            for (size_t i = 0; i < inputs.size(); ++i) {
                VectorD final_output = feedforward(inputs[i]);

                VectorD output_errors = errors(final_output, targets[i]);

                backpropagate(output_errors, learning_rate);
            }
        }
    }

private:
    Layer output_layer;
    Layers hidden_layers;

    VectorD errors(const VectorD& outputs, const VectorD& targets) {
        VectorD output_errors(outputs.size());
        for(size_t i = 0; i < outputs.size(); ++i) {
            output_errors[i] = targets[i] - outputs[i];
        }
        return output_errors;
    }

    double mean_squared_error(const VectorD& outputs, const VectorD& targets) {
        double error = 0.0;
        for (size_t i = 0; i < outputs.size(); ++i) {
            error += (targets[i] - outputs[i]) * (targets[i] - outputs[i]);
        }
        return error / outputs.size();
    }
};