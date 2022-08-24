#include <iostream>
#include <vector>

// #include <ctype.h>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;

// abstract class for stack
template <typename StackType> class GenericStack {
    public:
        virtual bool full() = 0;
        virtual bool empty() = 0;
        virtual void push(StackType x) = 0;
        virtual StackType pop() = 0;
};

// array stack derived of abstract stack class
template <typename StackType> class GenericArrayStack : public GenericStack<StackType> {
    protected:
        StackType *arr = NULL;
        int size, top = 0;
    public:
        GenericArrayStack(int size = 5) {
            this->size = size;
            this->arr = new StackType[size];
        }
        ~GenericArrayStack() {
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
            else{
                cout << "EMPTY!" << endl;
                StackType x;
                return x;
            }
        }
};

template <typename T> class PalindromeStack : public GenericArrayStack<T> {
    public:
        PalindromeStack(int size) : GenericArrayStack<T>(size) {}
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

        void printArr() {
            cout << this->arr << endl;
        }
};

template <typename T, typename T2> class PostfixStack : public GenericArrayStack<T> {
    public:
        PostfixStack(int size = 5) : GenericArrayStack<T>(size) {}

        void push(T2 x) {
            bool digit = true;
            forcn(i, digit, x.size()){
                if( ! isdigit(x[i]) )
                    digit = false;
            }
            if (digit){
                int y = stoi(x);
                GenericArrayStack<T>::push(y);
            }
            else{
                if(x == "+") {
                   int a = this->pop(), b = this->pop();
                   int c = a + b;
                   this->GenericArrayStack<T>::push(c);
                }
                else if(x == "-") {
                   int a = this->pop(), b = this->pop();
                   int c = b - a;
                   this->GenericArrayStack<T>::push(c);
                }
                else if(x == "*") {
                   int a = this->pop(), b = this->pop();
                   int c = a * b;
                   this->GenericArrayStack<T>::push(c);
                }
                else if(x == "/") {
                   int a = this->pop(), b = this->pop();
                   int c = b / a;
                   this->GenericArrayStack<T>::push(c);
                }
            }
        }

        void printArr() {
            forn(i, this->top) {
                cout << this->arr[i] << " ";
            }
            cout << endl;
        }
};

template <typename T> class CheckStack : public GenericArrayStack<T> {
    private:
        int parenthesis, sqbrackets, braces;
    public:
        CheckStack(int size = 5) : GenericArrayStack<T>(size) {
            this->parenthesis = 0;
            this->sqbrackets = 0;
            this->braces = 0;
        }
        void push(T x) {
            this->check(x);
            GenericArrayStack<T>::push(x);
        }

        void check(T s) {
            if (s == "(")
                this->parenthesis++;
            else if (s == ")")
                this->parenthesis--;
            else if (s == "[")
                this->sqbrackets++;
            else if (s == "]")
                this->sqbrackets--;
            else if (s == "{")
                this->braces++;
            else if (s == "}")
                this->braces--;
        }

        bool status() {
            return 0 == this->parenthesis && 0 == this->sqbrackets && 0 == this->braces;
        }
};

void useStackPalindrome() {
    string s = "reconocer";
    PalindromeStack <char> *stack = new PalindromeStack<char>(s.size());
    forn(i, s.size()) {
        stack->push(s[i]);
    }

    cout << "palindromo? " << boolalpha << stack->is_palindrome() << endl;
    cout << "stack = ";
    stack->printArr();
    while (!stack->empty()) {
        cout << "pop: " << stack->pop() << endl;
    }

    
    delete stack;
}

void usePostfixStack(string s) {
    int pos = 0;
    PostfixStack<int, string>* stack = new PostfixStack<int, string>(s.size());

    while((pos = s.find(' ')) != string::npos) {
        stack->push(s.substr(0, pos));
        s.erase(0, pos + 1);
    }
    stack->push(s);
    stack->printArr();
}

void useCheckStack(string s) {
    CheckStack<string>* stack = new CheckStack<string>(s.size());
    forn(i, s.size()) {
        stack->push(s.substr(i, 1));
    }
    cout << "status: " << boolalpha << stack->status() << endl;
}

int main() {
    useStackPalindrome();
    usePostfixStack("2 3 5 * +");
    usePostfixStack("2 3 + 5 *");
    usePostfixStack("2 3 + 4 5 + * 9 4 - /");
    useCheckStack("({())}[]()");
    useCheckStack("({s(.)),}[)");
    return 0;
}