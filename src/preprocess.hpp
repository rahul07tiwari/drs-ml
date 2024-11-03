#pragma once
#include <vector>
#include <cstdint>
#include <string>

typedef std::vector<double> VectorD;
typedef std::vector<VectorD> MatrixD;

struct MNISTLabel { uint8_t label; };
struct MNISTImage { std::vector<uint8_t> pixels; };

struct DataSplit {
    MatrixD train_inputs, train_targets;
    MatrixD val_inputs, val_targets;
};

namespace MNIST {
    std::vector<MNISTImage> load_images(const std::string& filename);
    std::vector<MNISTLabel> load_labels(const std::string& filename);
    MatrixD load_processed_images(const std::string& filename);
    MatrixD load_processed_labels(const std::string& filename);
    DataSplit split_data(const MatrixD& inputs, const MatrixD& targets, 
                         const double& train_ratio = 0.8);
}

