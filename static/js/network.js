var network_data = null

document.addEventListener("DOMContentLoaded", async function () {
    const response = await fetch('models/network.json');
    network_data = await response.json();
    console.log("Neural Network data loaded successfully!");
});

function relu(x) { return Math.max(0, x); }
function sigmoid(x) { return 1 / (1 + Math.exp(-x)); }

function dotProduct(weights, inputs) {
    return weights.reduce((sum, w, i) => sum + w * inputs[i], 0);
}

function applyLayer(inputs, layerName) {
    const { weights, biases } = network_data[layerName];
    return weights.map((neuronWeights, i) => {
        const weightedSum = dotProduct(neuronWeights, inputs) + biases[i];
        return (layerName !== "output_layer") ? relu(weightedSum) : sigmoid(weightedSum);
    });
}

export async function predict(inputArray) {
    if (!network_data) {
        throw new Error("Network data not loaded.");
    }

    let activations = inputArray;

    Object.keys(network_data).forEach(layerName => {
        activations = applyLayer(activations, layerName);
    });

    return activations;
}