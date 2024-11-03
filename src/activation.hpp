#pragma once
#include <cmath>

typedef double(*ActFunc)(const double&);
typedef double(*ActFuncPrime)(const double&);

inline double relu(const double& x) { return x > 0.0 ? x : 0.0; }
inline double relu_prime(const double& x) { return x > 0.0 ? 1.0 : 0.0; }

inline double sigmoid(const double& x) { return 1.0 / (1.0 + std::exp(-x)); }
inline double sigmoid_prime(const double& x) { return x * (1.0 - x); }

inline double tanh_clone(const double &x) { return tanh(x); }
inline double tanh_prime(const double &x) { return 1.0 - tanhf(x) * tanhf(x); }

enum Activation { SIGMOID, RELU, TANH };

inline ActFunc activation_func(Activation type) {
    switch (type) {
        case SIGMOID: return sigmoid;
        case RELU: return relu;
        case TANH: return tanh_clone;
        default: return sigmoid;
    }
}

inline ActFuncPrime activation_prime_func(Activation type) {
    switch (type) {
        case SIGMOID: return sigmoid_prime;
        case RELU: return relu_prime;
        case TANH: return tanh_prime;
        default: return sigmoid_prime;
    }
}

