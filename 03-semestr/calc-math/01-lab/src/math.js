/* math.js */

export let eps = 10 ** -5;
export const setEps = (newEps) => eps = newEps;

export const derivative = (f) => (x) => (f(x + eps) - f(x)) / eps;

export const secondDerivative = (f) => derivative(derivative(f));
