#include <iostream>
#include <vector>
#include "node.h"

// #include <ctype.h>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;
template <typename T> class Stack {
    private:
        Node<T>* top = NULL;
        int size;
    public:
        Stack(){
            this->size = 0;
        }

        ~Stack() {
            delete top;
            cout << "eliminando stack: " << typeid(T).name() << endl;
        }

        void push(T x) {
            Node<T>* n = new Node<T>(x);
            n->setNext(this->top);
            this->top = n;
            this->size++;
        }

        T pop() {
            Node<T>* n = this->top->getNext();
            this->top->setNext(NULL);
            T a = this->top->getData();
            Node<T>* m = new Node<T>(a);
            delete this->top;
            this->top = n;
            n = NULL;
            return a;
        }
        
        void printStack() {
            Node<T> *aux = this->top;
            while (aux->getNext() != NULL) {
                cout << aux->getData() << " ";
                aux = aux->getNext();
            }
            cout << aux->getData() << endl;
            
        }
};

void test() {
    Stack<int> stack = Stack<int>();
    stack.push(5);
    stack.push(14);
    stack.push(50);
    cout << "imprimiendo stack:\t";
    stack.printStack();
    cout << endl;
    cout << "pop: " << stack.pop() << endl << endl;
    cout << "pop: " << stack.pop() << endl << endl;
    cout << "imprimiendo stack:\t";
    stack.printStack();

    Stack<string>* stack2 = new Stack<string>();
    vector<string> s {"aA", "bB", "cC", "dD", "eE"};
    forn(i, s.size()) {
        stack2->push(s[i]);
    }
    
    cout << "imprimiendo stack2:\t";
    stack2->printStack();
    delete stack2;
}

void undoColor() {
    vector<string> colors {"Blue", "Red", "Green"};
    Stack<string>* stack = new Stack<string>();
    stack->push(colors[1]);
    cout << "seleccionado color: " << colors[1] << endl;
    stack->push(colors[0]);
    cout << "seleccionado color: " << colors[0] << endl;
    
    cout << "deshaciendo selección de color: " << stack->pop() << endl;
    cout << "colores seleccinados(primero es el actual): ";
    stack->printStack();
    cout << endl;

    
}

int main() {
    test();
    undoColor();
}