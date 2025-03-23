const user = {}
console.log(user.name) // undefinede

const userA = {
    name: "Nick",
    age: 32,
    address: {
        country: 'South Korea',
        city: 'Seoul'
    }
}

const userB = {
    name: "json",
    age: 22,
}

function getCity(user) {
    return user.address?.city || 'City is not available'
}

console.log(getCity(userA))
console.log(getCity(userB)) // error