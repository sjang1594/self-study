// CallBack

const a = (callBack) => {
    // callBack()
    console.log('A');
    callBack() // b()
}

const b = () => {
    console.log('B');
}

// parameter as function data -> callBack
a(b)

const sum = (a, b, c) => {
    setTimeout(() => {
        c(a + b)
    }, 1000)
}

sum(1, 2, (value) => {
    console.log(value)
})

sum(3, 7, value => {
    console.log(value)
})


// https://www.gstatic.com/webp/gallery/1.webp

const loadImage = (url, cb) => {
    const imgEl = document.createElement('img')
    imgEl.src = url
    imgEl.addEventListener('load', () => {
        // cb(imgEl)
        setTimeout(() => {
            cb(imgEl)
        }, 1000)
    })
}

const containerEl = document.querySelector('.container')
loadImage('https://www.gstatic.com/webp/gallery/1.webp', (imgEl) => {
    containerEl.innerHTML = ''
    containerEl.append(imgEl)
})