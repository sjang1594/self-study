for (let i = 0; i < 10; i++)
{
    console.log(i)
}

for (let i = 10; i > 0; i--)
{
    console.log(i)
}

// For of Loop
const fruits = ['Apple', 'Banana', 'Cherry']

for (const fruit of fruits) {
    console.log(fruit)
}

const users = [
    {
        name: "Nick",
        age: 32
    },
    {
        name: "Neo",
        age: 28
    },
    {
        name: "John",
        age: 35
    }
]

for (const user of users) {
    console.log(user.name, user.age)
}

const userInfo = {
    name: "Nick",
    age: 32,
    email: "nicks@mail.com",
    isValid: true
}

for (const key in userInfo) {
    console.log(key, userInfo[key])
}