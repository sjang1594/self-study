// Arrow Function

// function sum() {}
// const sum = function() {}
// const sum = () => {} // JavaScript ES6

const sum = (a, b) => a + b
console.log(sum(1, 2))

const a = () => {}
const b = x => {}
const c = (x, y) => {}
const e = x => x * x

console.log(e(5))

const g = () => { return { a: 1}}
const h = () => ({a : 1})

const i = () => { return [1, 2, 3]}
const j = () => [1, 2, 3]