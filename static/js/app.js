const canvas = document.getElementById('digit-canvas');
const submit = document.getElementById('submit-canvas');
// const clear = document.getElementById('clear-canvas');

const ctx = canvas.getContext('2d');
ctx.lineWidth = 20;
ctx.lineCap = 'round';
ctx.strokeStyle = 'black';
let is_drawing = false;

canvas.addEventListener('mousedown', (e) => {
    is_drawing = true;
    ctx.beginPath();
    ctx.moveTo(e.offsetX, e.offsetY);
});

canvas.addEventListener('mousemove', (e) => {
    if (is_drawing) {
        ctx.lineTo(e.offsetX, e.offsetY);
        ctx.stroke();
    }
});

['mouseup', 'mouseleave'].forEach(type => {
    canvas.addEventListener(type, () => { 
        is_drawing = false; 
        ctx.closePath();
    });
});

// clear.addEventListener('click', ()=>{
//     ctx.clearRect(0, 0, canvas.width, canvas.height);
// });

submit.addEventListener('click', () => {
    const gridSize = 28;
    const cellWidth = canvas.width / gridSize;
    const cellHeight = canvas.height / gridSize;
    const binaryArray = [];

    for (let y = 0; y < gridSize; y++) {
        for (let x = 0; x < gridSize; x++) {
            const centerX = Math.floor((x + 0.5) * cellWidth);
            const centerY = Math.floor((y + 0.5) * cellHeight);

            const imageData = ctx.getImageData(centerX, centerY, 1, 1);
            const pixels = imageData.data;

            const r = pixels[0];
            const g = pixels[1];
            const b = pixels[2];
            const alpha = pixels[3];

            const isBlack = (r < 128 && g < 128 && b < 128 && alpha === 255);

            binaryArray.push(isBlack ? 1 : 0);
        }
    }
    console.log(binaryArray);
});


