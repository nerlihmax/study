/* index.js */

/*
 * Лабораторная работа 1
 * Численные методы решения нелинейных уравнений
 * Вариант 15
 * Функция 4x-cos(x)-1=0
 * Методы 4, 5, x
 * Метод итераций, метод хорд и касательных, метод Ньютона
 */

import { solve } from './solve.js';
import { newton, iterative, chordsAndTangents } from './methods.js';
import { setEps, eps } from './math.js';

const f = (x) => 4 * x - Math.cos(x) - 1;

setEps(10 ** -5);

const a = -5;
const b = 10;

console.log(`a = ${a}; b = ${b}; eps=${eps};`);
console.log('\n');

solve(newton)(f, a, b);
solve(iterative)(f, a, b);
solve(chordsAndTangents)(f, a, b);
