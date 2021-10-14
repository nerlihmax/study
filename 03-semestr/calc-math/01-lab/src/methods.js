/* methods.js */

import { derivative, secondDerivative, eps } from './math.js';

export const chordsAndTangents = (f, a, b) => {
  let iterations = 0;

  if (f(a) * f(b) >= 0) 
    return { result: 'n/a', iterations };

  while (true) {
    if (f(a) * secondDerivative(f)(a) < 0)
      a = a - f(a) * (a - b) / (f(a) - f(b));
    else if (f(a) * secondDerivative(f)(a) > 0)
      a = a - f(a) / derivative(f)(a);

    if (f(b) * secondDerivative(f)(b) < 0)
      b = b - f(b) * (b - a) / (f(b) - f(a))
    else if (f(b) * secondDerivative(f)(b) > 0)
      b = b - f(b) / derivative(f)(b);

    iterations++;

    if (Math.abs(a - b) <= 2 * eps)
      return { result: (a + b) / 2, iterations };
  }
};

export const newton = (f, a, b) => {
  let x = 0;
  let iterations = 0;
  let checker = 0;

  if (f(a) * f(b) > 0) {
    return { result: 'n/a', iterations };
  }

  if (f(a) * secondDerivative(f)(a) > 0) {
    x = a;
  } else {
    x = b;
  }

  while (Math.abs(checker - x) > eps) {
    x -= f(x) / derivative(f)(x);
    checker = x - f(x) / derivative(f)(x);
    iterations++;
  }

  return { result: x, iterations };
};

export const iterative = (f, a, b) => {
  const iter = (f) => (x, L) => x + L * f(x);

  const L = -1/4;

  let x = (b + a) / 2;;
  let iterations = 0;
  let next = 0;

  while (Math.abs(next - x) > eps) {
    x = iter(f)(x, L);
    next = iter(f)(x, L);
    iterations++; 
  }

  return { result: x, iterations };
};
