#include <iostream>
#include <vector>
#include <string>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;

class Stack {
    private:
        int size, index = 0;
        char *arr = NULL;
    public:
        Stack (int size=5) {
            this->size = size;
            this->arr = new char[size];
        }
        ~Stack () {
            delete [] arr;
        }

        bool full() {
            return index == size;
        }

        bool empty() {
            return index == 0;
        }

        void push(char x) {
            if (! this->full()) {
                arr[index] = x;
                index++;
            }
            else
                cout << "full" << endl;
        }

        char pop() {
            if (! this->empty()) {
                index--;
                char a = arr[index];
                return a;
            }
            else
                cout << "lleno" << endl;
                return '\0';
        }

        bool is_palindrome() {
            bool palindrome = true;
            forcn(i, palindrome, size/2) {
                if (arr[i] != arr[index - 1 - i])
                    palindrome = false;
            }
            return palindrome;
        }

        void printArr() {
            cout << arr << endl;
        }
};


int main() {
    string s = "reconocer";
    Stack *stack = new Stack(s.size());
    forn(i, s.size()) {
        stack->push(s[i]);
    }
    cout << "palindromo?? " << boolalpha << stack->is_palindrome() << endl;
    cout << "pop: " << stack->pop() << endl;

    return 0;
}