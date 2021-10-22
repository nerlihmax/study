export const useCanvas = (config) => {
    const canvas = document.querySelector((config === null || config === void 0 ? void 0 : config.selector) || 'canvas');
    if (canvas === null)
        throw Error('bad selector');
    const ctx = canvas.getContext('2d');
    if (ctx === null)
        throw Error('bad context');
    ctx.scale(canvas.width / config.width, -canvas.height / config.height);
    ctx.translate(0, -config.height);
    ctx.lineWidth = 0.2;
    return {
        ctx,
    };
};
