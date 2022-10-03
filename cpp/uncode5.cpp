#include <iostream>
#define forn(i,n) for(int i=0;i<int(n);i++)

using namespace std;

template <typename T> class Node {
    public:
        T* data;
        Node<T>* next;
        Node<T>* prev;
        Node(T* x) {
            this->next = NULL;
            this->prev = NULL;
            this->data = x;
        }
        Node() {
            this->next = NULL;
            this->prev = NULL;
        }
        ~Node() {
            delete data, next, prev;
        }
};

template <typename T> class Stack {
    private:
        Node<T>* top = NULL;
    public:
        Stack(){
            this->size = 0;
        }

        ~Stack() {
            delete top;
        }

        void push(T x) {
            Node<T>* n = new Node<T>(x);
            n->next = this->top;
            this->top = n;
            this->size++;
        }

        T* pop() {
            Node<T>* n = this->top->next;
            this->top->next = NULL;
            T* a = this->top->data;
            Node<T>* m = new Node<T>(a);
            this->top = n;
            n = NULL;
            return a;
        }
};

template <typename T> class Queue {
    private:
        Node<T>* front;
        Node<T>* rear;
    public:
        Queue() {
            this->front = NULL;
            this->rear = NULL;
        }

        ~Queue() {
            delete front, rear;
        }

        void enqueue(T* i) {
            Node<T>* n = new Node<T>(i);

            if(this->rear != NULL) {
                this->rear->next = n;
                this->rear = n;
            } else {
                this->rear = n;
                this->front = n;
            }
        }

        T* dequeue() {
            T* a;
            if(! this->empty()) {
                a = this->front->data;
                Node<T>* aux = this->front;
                this->front = this->front->next;
                aux->next = NULL;
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
};

int main() {
    int casos;
    cin >> casos;

    Queue<string>* electrodomesticos = new Queue<string>();
    forn(i, casos) {
        int n_e, tiendas;
        cin >> n_e;
        string* s;
        forn(j, n_e) {
            s = new string();
            cin >> *s;
            electrodomesticos->enqueue(s);
        }
        cin >> tiendas;
        int* n_et = new int[tiendas];
        forn(j, tiendas) {
            cin >> n_et[j];
        }

        forn(j, tiendas) {
            cout << "[";
            forn(k, n_et[j]) {
                if(electrodomesticos->empty()) continue;
                string* s = electrodomesticos->dequeue();
                cout << *s;
                if( !electrodomesticos->empty() && k != n_et[j]-1) cout << " ";
            }
            cout << "]" << endl;
        }

        while( !electrodomesticos->empty()) {
            electrodomesticos->dequeue();
        }
    }
    return 0;
}