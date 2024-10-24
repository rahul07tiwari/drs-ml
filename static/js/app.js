function getPixelArray() {
    const gridSize = 28; // We'll map the canvas to a 28x28 grid
    const cellWidth = canvas.width / gridSize;
    const cellHeight = canvas.height / gridSize;
    const binaryArray = [];

    for (let y = 0; y < gridSize; y++) {
        for (let x = 0; x < gridSize; x++) {
            let pixelFound = false;

            // Loop through each pixel in the grid cell
            for (let cellY = Math.floor(y * cellHeight); cellY < Math.floor((y + 1) * cellHeight); cellY++) {
                for (let cellX = Math.floor(x * cellWidth); cellX < Math.floor((x + 1) * cellWidth); cellX++) {
                    const imageData = ctx.getImageData(cellX, cellY, 1, 1);
                    const pixels = imageData.data; // RGBA values for the current pixel

                    const r = pixels[0];
                    const g = pixels[1];
                    const b = pixels[2];
                    const alpha = pixels[3];

                    // If the pixel is close to black and fully opaque, mark the grid cell as "activated"
                    if (r < 128 && g < 128 && b < 128 && alpha === 255) {
                        pixelFound = true;
                        break; // No need to check further, one black pixel is enough to activate the grid cell
                    }
                }
                if (pixelFound) break; // Exit once we find an activated pixel
            }

            // Add 1 if any black pixel was found, otherwise add 0
            binaryArray.push(pixelFound ? 1 : 0);
        }
    }

    console.log(binaryArray); // Prints the binary array to the console
}



// ---------------------------------------- Draw ------------------------------------------ //

const canvas = document.getElementById('digitCanvas');
const ctx = canvas.getContext('2d');
let isDrawing = false;

// Function to start drawing when the mouse is pressed down
canvas.addEventListener('mousedown', (e) => {
    isDrawing = true;
    ctx.lineWidth = 8; // Adjust this for boldness (e.g., 20 for thicker strokes)
    ctx.lineCap = 'round'; // Makes the stroke smooth and rounded
    ctx.strokeStyle = '#000'; // Set stroke color to black
    ctx.beginPath();
    ctx.moveTo(e.offsetX, e.offsetY);
});

// Function to draw while the mouse moves
canvas.addEventListener('mousemove', (e) => {
    if (isDrawing) {
        ctx.lineTo(e.offsetX, e.offsetY);
        ctx.stroke();
    }
});

// Function to stop drawing when the mouse is released
canvas.addEventListener('mouseup', () => {
    isDrawing = false;
    ctx.closePath();
});

// Function to clear the canvas
function clearCanvas() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
}
