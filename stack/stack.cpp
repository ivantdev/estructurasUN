#include <iostream>
#include <string>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;

template <typename StackType> class GenericStack {
    protected:
        StackType *arr = NULL;
        int size, top = 0;
    public:
        GenericStack(int size = 5) {
            this->size = size;
            this->arr = new StackType[size];
        }
        ~GenericStack() {
            delete [] this->arr;
        }

        bool full() {
            return this->top == this->size;
        }

        bool empty() {
            return this->top == 0;
        }

        void push(StackType x) {
            if (! this->full()) {
                this->arr[this->top] = x;
                this->top++;
            }
            else
                cout << "full" << endl;
        }

        StackType pop() {
            if (! this->empty()) {
                this->top--;
                return this->arr[this->top];
            }
            else
                return 1;
        }

        void printArr() {
            cout << this->arr << endl;
        }
};

template <typename T> class PalindromeStack : public GenericStack<T> {
    public:
        PalindromeStack(int size = 5) : GenericStack<T>(size) {}
        bool is_palindrome() {
            bool palindrome = true;
            forcn(i, palindrome, this->size/2) {
                if (this->arr[i] != this->arr[this->size - 1 - i])
                    palindrome = false;
            }
            return palindrome;
        }
        int getSize() {
            return this->size;
        }
};

void useStackPalindrome() {
    string s = "reconocer";
    PalindromeStack <char> *stack = new PalindromeStack<char>(s.size());
    forn(i, s.size()) {
        stack->push(s[i]);
    }
    stack->printArr();
    cout << "pop: " << stack->pop() << endl;
    while (!stack->empty()) {
        cout << "pop: " << stack->pop() << endl;
    }
    
    cout << "pop: " << stack->pop() << endl;

    cout << "size of string: " << s.size() << endl;
    cout << "size of stack: " << s.size() << endl;
    cout << "palindromo? " << boolalpha << stack->is_palindrome() << endl;
    
    delete stack;
}

int main() {
    useStackPalindrome();
    return 0;
}