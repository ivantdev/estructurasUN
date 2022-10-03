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

template <typename T> class LinkedList {
    public:
        int size;
        Node<T>* head;
        Node<T>* tail;

        LinkedList() {
            this->size = 0;
            this->head = NULL;
            this->tail = NULL;
        }
        ~LinkedList() {
            delete head, tail;
        }

        bool empty() {
            return this->head == NULL;
        }

        bool find(T* data) {
            Node<T>* node = this->head;
            bool find = false;
            while(node->next != NULL) {
                if(data[0] <= node->data[0] && data[1] >= node->data[1]  && data[1] <= node->data[2]) {
                    find = true;
                    break;
                }
                node = node->next;
            }
            find = find || (data[0] <= node->data[0] && data[1] >= node->data[1]  && data[1] <= node->data[2]) ? true : false;
            return find;
        }

        void erase(T key) {
            Node<T>* node = this->head;
            while(node->data != key) {
                if( !node ) {
                    throw invalid_argument("Key not found!");
                }
                node = node->next;
            }
            node->prev->next = node->next;
            node->next->prev= node->prev;
            node->next = node->prev = NULL;
            delete node;
        }

        void pushFront(T* key) {
            Node<T>* newNode = new Node<T>(key);
            newNode->next = this->head;
            if (this->tail == NULL) {
                this->head = newNode;
                this->tail = this->head;
            } else {
                this->head->prev = newNode;
                this->head = newNode;
            }
            this->size++;
        }

        Node<T>* topFront() {
            if(this->head != NULL)
                return this->head;
            else {
                throw invalid_argument("Error: empty list!");
            }
        }

        void popFront() {
            if(this->head == NULL) {
                throw invalid_argument("Error: empty list!");
            } else if(this->head == this->tail){
                delete this->head;
                this->head = this->tail = NULL;
            } else {
                Node<T>* aux = this->head;
                this->head = aux->next;
                this->head->prev = NULL;
                aux->next = NULL;
                delete aux;
                this->tail = this->head == NULL ? NULL : this->tail;
            }
        }

        void pushBack(T* key) {
            Node<T>* newNode = new Node<T>(key);
            newNode->prev = this->tail;
            newNode->next = NULL;
            if (this->head == NULL) {
                this->head = this->tail = newNode;
            }
            else {
                this->tail->next = newNode;
                this->tail = newNode;
            }
            this->size++;
        }

        Node<T>* topBack() {
            if(this->tail != NULL)
                return this->tail;
            else {
                throw invalid_argument("Empty!");
            }
        }

        void popBack() {
            if(this->tail == NULL) {
                throw invalid_argument("Error: empty list!");
            } else if(this->head == this->tail){
                delete this->head;
                this->head = this->tail = NULL;
            } else {
                Node<T>* aux = this->tail;
                this->tail = aux->prev;
                this->tail->next = NULL;
                aux->prev = NULL;
                delete aux;
                this->head = this->tail == NULL ? NULL : this->head;
            }
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
    int n_horas, n_ing, n_clinetes;
    cin >> n_horas >> n_ing >> n_clinetes;

    LinkedList<int>* ingenieros = new LinkedList<int>();
    forn(i, n_ing) {
        int* data = new int[3];
        cin >> data[0] >> data[1] >> data[2];
        ingenieros->pushBack(data);
    }

    Queue<int>* clientes = new Queue<int>();
    forn(i, n_clinetes) {
        int* data = new int[2];
        cin >> data[0] >> data[1];
        clientes->enqueue(data);
    }

    while( !clientes->empty() ){
        int* cliente = clientes->dequeue();
        if (ingenieros->find(cliente)) cout << "YES" << endl;
        else cout << "NO" << endl;
        delete cliente;
    }

    
    return 0;
}