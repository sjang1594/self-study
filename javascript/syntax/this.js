const user = {
    firestName: 'Nick',
    lastName: 'Doe',
    age: 32,
    getFullName: function() {
        return `${this.firestName} ${this.lastName}`
    }
}

console.log(user.getFullName()) // Nick Doe

const lewis = {
    firestName: 'Lewis',
    lastName: 'Hamilton',
}

console.log(user.getFullName.call(lewis)) // Lewis Hamilton

const timer =  {
    title: 'TIMER!',
    timeout() {
        console.log(this.title)
        setTimeout( () => {
            console.log(this.title)
        }, 1000)
    }
}