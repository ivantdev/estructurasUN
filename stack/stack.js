class Stack {
    constructor (size=5) {
        this.arr = [];
        this.arr.length = size;
        this.idx = 0;
    }

    full () {
        return this.arr.length === this.idx;
    }

    empty() {
        return this.idx === 0;
    }

    push(x) {
        if(! this.full()) {
            this.arr[this.idx] = x;
            this.idx++;
            return;
        } else {
            console.log('full');
            return;
        }
    }

    empty() {
        if(! this.empty()) {
            this.idx--;
            const last = this.arr[this.idx];
            return last;
        } else {
            console.log('vacio');
            return;
        }
    }

    is_palindrome() {
        let palindrome = true;
        for(let i = 0; i < this.arr.length/2 && palindrome; i++) {
            if(this.arr[i] != this.arr[this.arr.length - 1 - i])
                palindrome = false;
        }
        return palindrome;
    }
}
const string = "reconocer";
const stack = new Stack(string.length)
for(let i = 0; i < string.length; i++) {
    stack.push(string[i]);
}
console.log(stack.is_palindrome());