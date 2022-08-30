#include <iostream>
#include "../stack/node.h"

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;

// template <typename T> class Queue {
//     private:
//         int front, rear, size, count;
//         T* data = NULL;
//     public:
//         Queue(int n) {
//             this->data = new T[n];
//             this->front = 1;
//             this->rear = 0;
//             this->size = n;
//             this->count = 0;
//         }
//         void enqueue(T i) {
//             if (! this->full()){
//                 this->data[this->rear] = i;
//                 this->rear = (this->rear + 1) % this->size;
//                 this->count++;
//             } else {
//                 cout << "llenoo!" << endl;
//             }
//         }

//         T dequeue() {
//             if(! this->empty()) {
//                 this->front++;
//                 this->count--;
//                 return this->data[this->front-2];
//             } else {
//                 cout << "vacio!" << endl;
//                 T a;
//                 return a;
//             }
//         }

//         bool full() {
//             return this->count == this->size;
//         }

//         bool empty() {
//             return this->count == 0;
//         }

//         void print() {
//             cout << endl;
//             forn(i, size){
//                 cout << data[i] << endl;
//             }
//             cout << endl;
//         }
// };
template <typename T> class Queue {
    private:
        int size, count;
        Node<T>* front = NULL;
        Node<T>* rear = NULL;
    public:
        Queue(int n) {
            this->size = n;
            this->count = 0;
        }
        void enqueue(T i) {
            if (! this->full()){
                Node<T>* n = new Node<T>(i);
                
                if(this->rear != NULL) {
                    this->rear->setNext(n);
                    this->rear = n;
                } else {
                    this->rear = n;
                    this->front = n;
                }
            } else {
                cout << "llenoo!" << endl;
            }
        }

        T dequeue() {
            if(! this->empty()) {
                this->front++;
                this->count--;
            } else {
                cout << "vacio!" << endl;
                T a;
                return a;
            }
        }

        bool full() {
            return this->count == this->size;
        }

        bool empty() {
            return this->count == 0;
        }

        void print() {
            Node<T> *aux = this->front;
            while (aux->getNext() != NULL) {
                cout << aux->getData() << " ";
                aux = aux->getNext();
            }
            cout << aux->getData() << endl;
        }
};


int main() {
    Queue<int>* cola = new Queue<int>(4);
    cola->dequeue();
    cola->enqueue(1);
    cola->enqueue(2);
    cola->enqueue(3);
    cola->enqueue(4);
    cola->enqueue(4);
    cola->print();
    cout << "dequeue: " <<  cola->dequeue() << endl;
    cout << "dequeue: " <<  cola->dequeue() << endl;
    return 0;
}