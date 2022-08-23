#include <iostream>
#include <vector>
#include <string>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;

template <typename T> class GenericStack {
    private:
        T *arr = NULL;
        int size, top = 0;
    public:
        GenericStack(int size = 5) {
            this->size = size;
            this->arr = new T[size];
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

        void push(T x) {
            if (! this->full()) {
                this->arr[this->top] = x;
                this->top++;
            }
            else
                cout << "full" << endl;
        }

        T pop() {
            if (! this->empty()) {
                this->top--;
                T a = this->arr[this->top];
                return a;
            }
            else
                return '\0';
        }

        void printArr() {
            cout << this->arr << endl;
        }
};

int main() {
    string s = "reconocer";
    GenericStack <char> *stack = new GenericStack<char>(s.size());
    forn(i, s.size()) {
        stack->push(s[i]);
    }
    stack->printArr();
    cout << "pop: " << stack->pop() << endl;
    while (!stack->empty()) {
        cout << "pop: " << stack->pop() << endl;
    }
    
    cout << "pop: " << stack->pop() << endl;
    
    delete stack;

    return 0;
}