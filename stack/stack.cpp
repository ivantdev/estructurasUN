#include <iostream>
#include <string>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;

template <typename StackType> class GenericStack {
    private:
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