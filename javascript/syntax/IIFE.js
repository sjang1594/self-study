// IIFE, Immediately-Invoked Function Expression

const a = 7
const double = () => a * 2

double()

;(() => {
    console.log(a * 2)
})()

;(() => { console.log(a * 2) })()            // (F)()
;(function () { console.log(a * 2) })()      // (F)()
;(function () { console.log(a * 2) }())     // ((F))
;!function () { console.log(a * 2) }        // !F()
;+function () { console.log(a * 2) }       // +F()

;((a, b) => {
    console.log(a * b)
})(1, 2)

// ex
;((a, b) => {
    console.log(a.innerWidth)
    console.log(b.body)
})(window, document)