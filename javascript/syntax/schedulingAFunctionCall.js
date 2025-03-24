
const hello = () => {
    console.log('Hello')
}

const timeout = setTimeout(hello, 2000)
const h1EL = document.querySelector('h1')
h1EL.addEventListener('click', () => {
    console.log('Clear')
    clearInterval(timeout)
})