import { predict } from './network.js';

document.addEventListener('DOMContentLoaded', function() {
    const canvas = document.getElementById('input-screen');
    const submit = document.getElementById('submit-canvas');
    const predictionsList = document.getElementById('top-predictions');
    
    const ctx = canvas.getContext('2d', { willReadFrequently: true });
    ctx.lineWidth = 35;
    ctx.lineCap = 'round';
    ctx.strokeStyle = 'white';
    var is_drawing = false;

    // Drawing functionality
    canvas.addEventListener('mousedown', function(e) {
        is_drawing = true;
        ctx.beginPath();
        ctx.moveTo(e.offsetX, e.offsetY);
    });

    canvas.addEventListener('mousemove', function(e) {
        if (is_drawing) {
            ctx.lineTo(e.offsetX, e.offsetY);
            ctx.stroke();
        }
    });

    ['mouseup', 'mouseleave'].forEach(function(type) {
        canvas.addEventListener(type, function() {
            is_drawing = false;
            ctx.closePath();
        });
    });

    // Submit functionality
    submit.addEventListener('click', function() {
        var gridSize = 28;
        var cellWidth = canvas.width / gridSize;
        var cellHeight = canvas.height / gridSize;
        var binaryArray = [];

        // Convert drawn content into a 28x28 grid of 1s and 0s
        for (var y = 0; y < gridSize; y++) {
            for (var x = 0; x < gridSize; x++) {
                var centerX = Math.floor((x + 0.5) * cellWidth);
                var centerY = Math.floor((y + 0.5) * cellHeight);
                var imageData = ctx.getImageData(centerX, centerY, 1, 1);
                var pixels = imageData.data;
                var r = pixels[0];
                var g = pixels[1];
                var b = pixels[2];
                var alpha = pixels[3];
                var isWhite = (r > 128 && g > 128 && b > 128 && alpha === 255);
                binaryArray.push(isWhite ? 1 : 0);
            }
        }

        // Get prediction probabilities
        predict(binaryArray).then(function(probabilities) {
            // Find the top 5 predictions
            var top5 = probabilities
                .map(function(prob, index) {
                    return { disease: 'Digit ' + index, probability: prob };
                })
                .sort(function(a, b) {
                    return b.probability - a.probability;
                })
                .slice(0, 5);

            // Display the top 5 predictions
            predictionsList.innerHTML = '';
            top5.forEach(function(item) {
                var listItem = document.createElement('li');
                listItem.textContent = item.disease + ': ' + Math.round(item.probability * 100) + '%';
                predictionsList.appendChild(listItem);
            });
        });
    });
});
