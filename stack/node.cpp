#include <iostream>
#include <vector>
#include <typeinfo>

// #include <ctype.h>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;

template <typename T> class Node {
    private:
        T data;
        Node<T>* next = NULL;
    public:
        Node(T x) {
            this->data = x;
        }

        ~Node() {
            cout << "eliminando nodo: " << typeid(T).name() << endl;
            delete next;
        }
        
        T getData() {
            return this->data;
        }

        void setNext(Node<T>* n) {
            this->next = n;
        }

        Node<T>* getNext() {
            return this->next;
        }
};

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
                cout << aux->getData() << endl;
                aux = aux->getNext();
            }
            cout << aux->getData() << endl;
            
        }
};

int main() {
    Stack<int> stack = Stack<int>();
    stack.push(5);
    stack.push(14);
    stack.push(50);
    stack.printStack();
    cout << "pop: " << stack.pop() << endl;
    cout << "pop: " << stack.pop() << endl;
    stack.printStack();

    Stack<string>* stack2 = new Stack<string>();
    vector<string> s {"aA", "bB", "cC", "dD", "eE"};
    forn(i, s.size()) {
        stack2->push(s[i]);
    }
    stack2->printStack();
    delete stack2;
}