#pragma once
#include <cmath>

#ifdef RELU_ACTIVATION
inline double relu(const double& x) { return x > 0.0 ? x : 0.0; }
inline double relu_prime(const double& x) { return x > 0.0 ? 1.0 : 0.0; }
#endif

#ifdef SIGMOID_ACTIVATION
inline double sigmoid(const double& x) { return 1.0 / (1.0 + std::exp(-x)); }
inline double sigmoid_prime(const double& x) { return x * (1.0 - x); }
#endif

#ifdef TANH_ACTIVATION
inline double tanh_prime(const double &x) { 
    const double tanh_x = tanhf(x);
    return 1.0 - tanh_x * tanh_x;
}
#endif
