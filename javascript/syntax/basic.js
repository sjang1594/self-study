// String
console.log("............String............")
const string1 = "Hello"
const string2 = 'Hello'
const string3 = `Hello ${string1} ?!`

console.log(string3)

// Int & float
console.log("............Number............")
const number = 123
const pi = 3.14
console.log(number + 1)
console.log(pi)
console.log(number + undefined) // NaN
console.log(typeof(number + undefined))

// Operations
const a = 0.1
const b = 0.2

console.log(a + b)                      // 0.3 -> floating error
console.log((a+b).toFixed(1))           // 0.3 -> string (typeof)
console.log(Number((a+b).toFixed(1)))   // 0.3 -> number (typeof)

// Boolean
console.log("............Boolean............")
const a_ = true
const b_ = false

if (a) {
    console.log('a is true')
}

// Null
console.log("............Null............")
let age = null // or undefined (implicit)

// console.log(age)
// setTimeout(function () {
//     age = 85
//     console.log(age)
// }, 1) // ms -> 1s

// Array (Reference Type)
console.log("............Array............")
const fruits1 = new Array('Apple', 'Banana', 'Cherry')
const fruits2 = ['Apple', 'Banana', 'Cherry'] // array literal
console.log(fruits1) 
console.log(fruits2) 
console.log(fruits1[0])
console.log(fruits1.length)
console.log("Item")
console.log(fruits2[fruits2.length-1])

// Objects (Reference Type)
console.log("............Object............")
const userObject = new Object()
userObject.name = "Nick"
userObject.age = 30

// key-value pair
console.log(userObject)

function User() {
    this.name = "Jason",
    this.age = 85
}

const userJason = new User()
console.log(userJason)

const user = { // literal
    name: "Nick",
    age: 85,
    email: null
}

console.log(user)
console.log(user.email) // undefined (explicit)

// Multiple Depth
const userA = {
    name: "Nick",
    age: 32
}

const userB = {
    name: "Neo",
    age: 28,
    parent: userA
}

console.log(userB)
console.log(userB.parent.name)
console.log(userB['parent']['age'])

const users = [userA, userB]
console.log(users[0])
console.log(users[1].name)

// Functions (Reference Type)
console.log("............Function............")
function hello() {
    console.log('Hello')
}

hello() // call
console.log(hello) // reference (function is data type)

function getNumber() {
    return 123
}

console.log(getNumber())
console.log(typeof getNumber())
console.log(typeof getNumber)

const getAge = function() {
    return 32
} // annoymous function

console.log(typeof getNumber())

const d = function (c) {
    console.log(c)
    console.log(getAge())
}

d([1,2,3])
d(getAge)

console.log("............Type Conversion............")
const k = 1
const bStr = '1'
console.log(k === bStr) // strict equal operator (data type)
console.log(k == bStr) // equal operator (type converted)

// Truthy & Falsy
console.log("............Truthy & Falsy............")
if(123) { // truthy
    console.log('Truthy')
}

if('0') {
    console.log('Truthy')
}

// Falsy
// 0
// false
// null & defined (implicit & explicit)
// NaN
// ''
// -0
// 0n (bitint)
if(0) {
    console.log('Falsy')
}

if('') {
    console.log('Falsy')
}

if(-0) {
    console.log('Falsy')
}

if(0n) { // bitint
    console.log('Falsy')
}

// Check Type
console.log("............Check Type............")
console.log(typeof 'Hello' === 'string')
console.log(typeof 123 === 'number')
console.log(typeof true === 'boolean')
console.log(typeof undefined === 'undefined')
console.log(typeof null === 'undefiend') // false
// object
console.log(typeof null === 'object')
console.log(typeof [] === 'object')
console.log(typeof {} === 'object')
console.log(typeof function() {} === 'function')
console.log([].constructor === Array)
console.log({}.constructor === Object)
console.log(Object.prototype.toString.call(null).slice(8, -1) === 'Null') // null check

// Check Type Function
function checkType(data) {
    return Object.prototype.toString.call(data).slice(8, -1)
}

console.log(checkType(null))
console.log(checkType([]))

// Nullish (Coalecsing)
console.log("............Nullish............")
const n = 0
const num1 = n || 7
console.log(num1)

const num2 = n ?? 7
console.log(num2)
console.log(null ?? 1) // null and undefined skip -> 1
console.log(undefined ?? 2)
console.log(null ?? undefined)
console.log(null ?? 1 ?? 2) // 1
console.log(false ?? 1 ?? 2)

// Spread Operator
const listA = [1, 2, 3]
const listB = [4, 5, 6]
console.log(...listA)
const listC = listA.concat(listB)
console.log(...listC)
const listD = [...listA, ...listB]
console.log(listD)

const ObjA = { x : 1, y : 2}
const ObjB = {y: 3, z :4}

const ObjC = Object.assign({}, ObjA, ObjB)
console.log(ObjC)
const ObjD = {...ObjA, ...ObjB}

function func_(x, y, z)
{
    console.log(x, y, z)
}

const ArrA = [1,2,3]
func_(...ArrA)