#ifndef __NEURON_HPP__
#define __NEURON_HPP__

#include <iostream>
#include <numeric>
#include <vector>
#include <random>
#include <cmath>

enum ActivationFunction { SIGMOID, RELU };

class Neuron {
public:
    Neuron(double bias, std::vector<double>& weights, ActivationFunction type)
    :bias(bias), weights(weights), activation_func(type) {}

    Neuron(size_t num_weights, ActivationFunction type): activation_func(type)
    {
        std::mt19937 rand(std::random_device{}());
        std::uniform_real_distribution<float> distribution(-1.0, 1.0);

        for(size_t i = 0; i < num_weights; ++i) {
            weights.push_back(distribution(rand));
        }
        this->bias = distribution(rand);
    }

    double feed_forward(const std::vector<double>& inputs) {
        if(inputs.size() != weights.size()) {
            throw std::invalid_argument("Input size and weight size must match!");
        }
        double dot_prod = dot_product(weights, inputs);
        return activation_function(dot_prod + bias);
    }

    const double& get_bias() const { return bias; }
    void set_bias(double new_bias) { bias = new_bias; }
    const std::vector<double>& get_weights() const { return weights; }
    void set_weights(std::vector<double> new_weights) { weights = new_weights; }

private:
    double bias;
    std::vector<double> weights;
    ActivationFunction activation_func;
    double relu(double x) { return x > 0 ? x : 0; }
    double sigmoid(double x) { return 1.0 / (1.0 + std::exp(-x)); }

    double activation_function(double x) {
        switch(activation_func) {
            case SIGMOID: return sigmoid(x);
            case RELU: return relu(x);
            default: return sigmoid(x);
        }
    }

    double dot_product(const std::vector<double>& x, const std::vector<double>& y) {
        return std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
    }
};

#endif // __NEURON_HPP__
