/* solve.js */

export const solve = (method) => (f, a, b) => {
  const methodName = method.name;
  
  const begin = performance.now();

  const { result, iterations } = method(f, a, b);

  const end = performance.now();

  const time = end - begin;

  console.log(`method: ${methodName}`);
  console.log(`result: ${result.toString().slice(0, 6)}`);
  console.log(`iterations: ${iterations}`);
  console.log(`execution time: ${time.toString().slice(0, 6)}`);
  console.log('\n');
};
