export const cda = (c) => ({ x1, y1, x2, y2, color }) => {
    const getXY = (x, y) => {
        const newX = dx >= 0 ? Math.floor(x) : Math.ceil(x);
        const newY = dy >= 0 ? Math.floor(y) : Math.ceil(y);
        return [newX, newY];
    };
    const length = Math.max(Math.abs(x2 - x1), Math.abs(y2 - y1));
    const dx = (x2 - x1) / length;
    const dy = (y2 - y1) / length;
    let x = x1 + 0.5 * Math.sign(dx);
    let y = y1 + 0.5 * Math.sign(dy);
    c.fillStyle = color;
    for (let i = 0; i <= length; i++) {
        c.fillRect(...getXY(x, y), 1, 1);
        x += dx;
        y += dy;
    }
};
