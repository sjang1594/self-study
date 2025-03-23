// hoisting

hello()

function hello() {
    console.log('Hello')
}


// intro() // Error

const intro = function intro() {
    console.log('Introduction')
}

intro() // Works

// Parameters Pattern
const user = {
    name: "Nick",
    email: "email",
    age: 32
}

function getName({ name }) {
    return name
}

const email = "Yes"

function getEmail( { email }) {
    return email
}

function getAddress( { address = "not available" }) {
    return address
}

console.log(getName(user))
console.log(getEmail(user))


const furuits = ['Apple', 'Banana', 'Cherry']
function getSecondItem( [, b]) {
    return b
}

const numbers = [1, 2, 3, 4, 5, 6, 7]
console.log(getSecondItem(numbers))

function sum(...rest) {
    return rest.reduce(function (acc, cur) {
        return acc + cur
    }, 0)
}

console.log(sum(1, 2))
console.log(sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
console.log(sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12))