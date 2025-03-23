// Destructuring Assignment

const arr = [1, 2, 3]
// const a = arr[0]
// const b = arr[1]
// const c = arr[2]
const [a, b, c] = arr
console.log(a, b, c)

let d = 0
let e = 0
let f = 0
const arr1 = [1, 2, 3]
;[d, e, f] = arr1
console.log(d, e, f)

const arr_ = [1, 2, 3]
const [g, ...rest] = arr
console.log(g,rest)

const obj = {
    h: 1,
    i: 2,
    j: 3
}

// Get only h and i
const {h, i} = obj
console.log(h, i)

// Default value & otherwise undefined
const { x = 5 } = obj
console.log(x)

// Change the name in h to nick (key changes)
const { z= 4, h: nick} = obj
console.log(z, nick)