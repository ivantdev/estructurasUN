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

        ~Queue() {
            delete front, rear;
        }

        void enqueue(T i) {
            if (! this->full()){
                cout << "encolando: " << i << endl;
                Node<T>* n = new Node<T>(i);

                if(this->rear != NULL) {
                    this->rear->setNext(n);
                    this->rear = n;
                } else {
                    this->rear = n;
                    this->front = n;
                }
            } else {
                throw invalid_argument("Full Queue");
            }
        }

        T dequeue() {
            T a;
            if(! this->empty()) {
                a = this->front->getData();
                Node<T>* aux = this->front;
                this->front = this->front->getNext();
                aux->setNext(NULL);
                delete aux;
            } else {
                throw invalid_argument("Empty Queue");
                T a;
            }
            if(this->empty())
                this->rear = NULL;
            return a;
        }

        bool full() {
            return this->count == this->size;
        }

        bool empty() {
            return this->front == NULL;
        }

        T getData() {
            return this->front->getData();
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
    Queue<char>* queue = new Queue<char>(100);
    queue->enqueue('u');
    queue->enqueue('n');
    queue->enqueue('a');
    queue->enqueue('l');
    queue->enqueue('!');

    cout << "la cola tiene lo siguiente:  ";
    queue->print();
    cout << "dequeue: " <<  queue->dequeue() << endl;
    cout << "dequeue: " <<  queue->dequeue() << endl;
    cout << "primer elemento de la cola: " << queue->getData() << endl;

    delete queue;
    return 0;
}