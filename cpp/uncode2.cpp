#include <iostream>
#define forn(i,n) for(int i=0;i<int(n);i++)

using namespace std;

template <typename T> class Node {
    public:
        T data;
        Node<T>* next;
        Node<T>* prev;
        Node(T x) {
            this->next = NULL;
            this->prev = NULL;
            this->data = x;
        }
        Node() {
            this->next = NULL;
            this->prev = NULL;
        }
};

template <typename T> class Queue {
    private:
        Node<T>* front, *rear;
    public:
        Queue() {
            this->front = this->rear = NULL;
        }

        ~Queue() {
            delete front, rear;
        }

        void enqueue(T i) {
            Node<T>* n = new Node<T>(i);

            if(this->rear != NULL) {
                this->rear->next = n;
                this->rear = n;
            } else {
                this->rear = n;
                this->front = n;
            }
        }

        T dequeue() {
            T a;
            if(! this->empty()) {
                a = this->front->data;
                Node<T>* aux = this->front;
                this->front = this->front->next;
                aux->next = NULL;
                delete aux;
            } else {
                throw invalid_argument("Empty Queue");
                T a;
            }
            if(this->empty())
                this->rear = NULL;
            return a;
        }

        bool empty() {
            return this->front == NULL;
        }

        T getData() {
            return this->front->data;
        }
};

template <typename T> class LinkedList {
    public:
        Node<T>* head;
        Node<T>* tail;

        LinkedList() {
            this->head = NULL;
            this->tail = NULL;
        }
        ~LinkedList() {
            delete head, tail;
        }

        bool empty() {
            return this->head == NULL;
        }

        bool find(T key) {
            Node<T>* node = this->head;
            bool find = false;
            while(node->next != NULL) {
                if(node->data == key) {
                    find = true;
                    break;
                }
                node = node->next;
            }
            find = find || node->data == key ? true : false;
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

        void pushFront(T key) {
            Node<T>* newNode = new Node<T>(key);
            newNode->next = this->head;
            if (this->tail == NULL) {
                this->head = newNode;
                this->tail = this->head;
            } else {
                this->head->prev = newNode;
                this->head = newNode;
            }
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

        void pushBack(T key) {
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
        }

        T topBack() {
            if(this->tail != NULL)
                return this->tail->data;
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

template <typename T> class Stack {
    private:
        Node<T>* top;
    public:
        Stack(){
            this->top = NULL;
        }

        ~Stack() {
            delete top;
        }

        void push(T x) {
            Node<T>* n = new Node<T>(x);
            n->next = this->top;
            this->top = n;
        }

        T pop() {
            Node<T>* n = this->top->next;
            this->top->next = NULL;
            T a = this->top->data;
            Node<T>* m = new Node<T>(a);
            delete this->top;
            this->top = n;
            n = NULL;
            return a;
        }

        bool empty() {
            return this->top == NULL;
        }
};

int main() {
    string ao = "abcdefghijklmnopqrstuvwxyz";
    int t;
    string m;
    cin >> t >> m;

    // Usando colas
    Queue<char>* apq = new Queue<char>();
    forn(i, ao.size()) {
        apq->enqueue(ao[i]);
    }
    // Permutando el alfabeto
    char c;
    forn(i, t) {
        c = apq->dequeue();
        apq->enqueue(c);
    }

    // Pasando la cola a una lista enlazada
    LinkedList<char>* apl = new LinkedList<char>();
    while( !apq->empty() ) {
        apl->pushBack(apq->dequeue());
    }
    // Usando pila para invertir la cadena
    Stack<char>* aps = new Stack<char>();
    forn(i, m.size()) {
        c = m[i];

        // Buscar index del caracter en el alfabeto original y buscar su correspendiente permutación
        Node<char>* cur = apl->topFront();
        int idx = 0;
        while( ao[idx] != c ) {
            cur = cur->next;
            idx++;
        }

        // Apilamos el caracter de la permutación
        aps->push(cur->data);
    }

    // imprimimos cada elemento del stack eliminandolo
    while( !aps->empty() ) {
        cout << aps->pop();
    }

    cout << endl;

    return 0;
}