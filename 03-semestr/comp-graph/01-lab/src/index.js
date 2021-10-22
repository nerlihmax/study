import { useCanvas } from './canvas.js';
import { Colors } from './colors.js';
const cfg = {
    width: 50,
    height: 50,
    selector: 'canvas',
};
const { ctx } = useCanvas(cfg);
/* draw chess-like background */
for (let i = 0; i < cfg.width; i++) {
    for (let j = 0; j < cfg.height; j++) {
        if ((i % 2) === (j % 2))
            ctx.fillStyle = Colors.Gray;
        else
            ctx.fillStyle = Colors.White;
        ctx.fillRect(i, j, 1, 1);
    }
}
