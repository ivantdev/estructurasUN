#include <iostream>

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
            cout << "eliminando nodo tipo: " << typeid(T).name() << endl;
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