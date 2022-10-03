#include <iostream>
#include <vector>
#define forn(i,n) for(int i=0;i<int(n);i++)

using namespace std;

template <typename T> class Node {
    public:
        T computer, laptops, tablets;
        Node<T>* next;
        Node<T>* prev;

        Node(T c, T l, T t) {
            this->next = NULL;
            this->prev = NULL;
            this->computer = c;
            this->laptops = l;
            this->tablets = t;
        }
};

template <typename T1,typename T2> class NodeLL {
    public:
        T1 facultad;
        T2 faltantes;
        int computer, laptops, tablets;
        NodeLL<T1, T2>* next;
        NodeLL<T1, T2>* prev;

        NodeLL(T1 x, T2 y) {
            this->next = NULL;
            this->prev = NULL;
            this->facultad = x;
            this->faltantes = y;
            this->computer = this->laptops = this->tablets = 0;
        }
        NodeLL() {
            this->next = NULL;
            this->prev = NULL;
        }
};

template <typename T1,typename T2> class LinkedList {
    public:
        int size;
        NodeLL<T1, T2>* head;
        NodeLL<T1, T2>* tail;

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

        void pushFront(T1 fac, T2 est) {
            NodeLL<T1, T2>* newNodeLL = new NodeLL<T1, T2>(fac, est);
            newNodeLL->next = this->head;
            if (this->tail == NULL) {
                this->head = newNodeLL;
                this->tail = this->head;
            } else {
                this->head->prev = newNodeLL;
                this->head = newNodeLL;
            }
            this->size++;
        }

        NodeLL<T1, T2>* topFront() {
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
                NodeLL<T1, T2>* aux = this->head;
                this->head = aux->next;
                this->head->prev = NULL;
                aux->next = NULL;
                delete aux;
                this->tail = this->head == NULL ? NULL : this->tail;
            }
        }

        void pushBack(T1 fac, T2 est) {
            NodeLL<T1, T2>* newNodeLL = new NodeLL<T1, T2>(fac, est);
            newNodeLL->prev = this->tail;
            newNodeLL->next = NULL;
            if (this->head == NULL) {
                this->head = this->tail = newNodeLL;
            }
            else {
                this->tail->next = newNodeLL;
                this->tail = newNodeLL;
            }
            this->size++;
        }

        NodeLL<T1, T2>* topBack() {
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
                NodeLL<T1, T2>* aux = this->tail;
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
        Node<T>* front, *rear;
    public:
        Queue() {
            this->front = this->rear = NULL;
        }

        ~Queue() {
            delete front, rear;
        }

        void enqueue(T c,T l,T t) {
            Node<T>* n = new Node<T>(c, l ,t);

            if(this->rear != NULL) {
                this->rear->next = n;
                this->rear = n;
            } else {
                this->rear = n;
                this->front = n;
            }
        }

        Node<T>* dequeue() {
            Node<T>* a;
            if(! this->empty()) {
                a = this->front;
                this->front = a->next;
                a->next = NULL;
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
};


void swapNodes(NodeLL<string, int>* node) {
    NodeLL<string, int>* n = node->next, *aux;
    if(node->prev != NULL)node->prev->next = n;
    if(n->next != NULL) n->next->prev = node;

    aux = node->prev;
    node->prev = n;
    n->prev = aux;

    node->next = n->next;
    n->next = node;
}

int getWeight(string s) {
    vector<string> v{"Ingenieria","Humanas","Medicina","Artes"};
    forn(i, 4) {
        if(s == v[i]) return i;
    }
    return 0;
}

// sort function
void sortLL(LinkedList<string, int>* lista) {
    forn(i, lista->size) {
        bool sorted = true;
        NodeLL<string, int>* node = lista->topFront();
        forn(j, lista->size-1) {
            if(node->faltantes == node->next->faltantes) {
                if(getWeight(node->facultad) > getWeight(node->next->facultad)){
                    if(j == 0) lista->head = node->next;
                    swapNodes(node);
                    sorted = false;
                    node = node->prev;
                }
            }
            if(node->faltantes > node->next->faltantes) {
                if(j == 0) lista->head = node->next;
                swapNodes(node);
                sorted = false;
            } else {
                node = node->next;
            }
        }
        if( sorted ) break;
    }
}
void sortLLReverse(LinkedList<string, int>* lista) {
    forn(i, lista->size) {
        bool sorted = true;
        NodeLL<string, int>* node = lista->topFront();
        forn(j, lista->size-1) {
            if(node->faltantes == node->next->faltantes) {
                if(getWeight(node->facultad) > getWeight(node->next->facultad)){
                    if(j == 0) lista->head = node->next;
                    swapNodes(node);
                    sorted = false;
                }
            }
            if(node->faltantes < node->next->faltantes) {
                if(j == 0) lista->head = node->next;
                swapNodes(node);
                sorted = false;
            } else {
                node = node->next;
            }
        }
        if( sorted ) break;
    }
}

int main() {
    string s;
    getline(cin, s);

    // guardar n-estudiantes sin acceso por facultad
    LinkedList<string, int>* facus = new LinkedList<string, int>();
    string subs;
    int x;
    forn(i, 3) {
        subs = s.substr(0,s.find(" "));
        s.erase(0,s.find(" ") + 1);
        x = stoi(s.substr(0, s.find(" ")));
        s.erase(0,s.find(" ") + 1);
        facus->pushBack(subs, x);
    }
    subs  = s.substr(0,s.find(" "));
    s.erase(0,s.find(" ") + 1);
    x = stoi(s);
    facus->pushBack(subs, x);

    s = "";
    Queue<int>* lotes = new Queue<int>();
    while(getline(cin, s)) {
        if(s.find("Lote ") != -1) {
            s.erase(0, 15);
            int c = stoi(s.substr(0, s.find(" ")) );
            s.erase(0, s.find(" ") + 9);
            int l = stoi(s.substr(0, s.find(" ")) );
            s.erase(0, s.find(" ") + 9);
            int t = stoi(s);
            
            lotes->enqueue(c, l, t);
        }
        if(s == "Distribuir lote") {
            sortLLReverse(facus);
            Node<int>* lote = lotes->dequeue();
            NodeLL<string, int>* facultad = facus->topFront();
            int i = 0;
            while (lote->computer > 0 || lote->laptops > 0 || lote->tablets > 0) {
                if(facultad->faltantes > 0 && lote->computer > 0 && i%3 == 0) {
                    facultad->faltantes--;
                    facultad->computer++;
                    lote->computer--;
                    i++;
                }else if(lote->computer == 0 && facultad->faltantes > 0) i++;

                if(facultad->faltantes > 0 && lote->laptops > 0 && i%3 == 1) {
                    facultad->faltantes--;
                    facultad->laptops++;
                    lote->laptops--;
                    i++;
                } else if(lote->laptops == 0 && facultad->faltantes > 0) i++;

                if(facultad->faltantes > 0 && lote->tablets > 0 && i%3 == 2) {
                    facultad->faltantes--;
                    facultad->tablets++;
                    lote->tablets--;
                    i++;
                } else if(lote->tablets == 0 && facultad->faltantes > 0) i++;
                
                if((facultad->faltantes == 0 && facultad->next == NULL) || (lote->computer ==0 && lote->laptops == 0 && lote->tablets == 0 && facultad->next == NULL)) {
                    break;
                } else if(facultad->faltantes == 0) {
                    facultad = facultad->next;
                }
            }
        }
        if(s == "Imprimir") {
            sortLL(facus);
            NodeLL<string, int>* facultad = facus->topFront();
            while(facultad->next != NULL) {
                cout << facultad->facultad << " " << facultad->faltantes;
                cout << " - Computers " << facultad->computer;
                cout << " Laptops " << facultad->laptops;
                cout << " Tablets " << facultad->tablets << endl;;
                facultad->computer = facultad->laptops = facultad->tablets = 0;
                facultad = facultad->next;
            }
            cout << facultad->facultad << " " << facultad->faltantes;
            cout << " - Computers " << facultad->computer;
            cout << " Laptops " << facultad->laptops;
            cout << " Tablets " << facultad->tablets << endl;
                facultad->computer = facultad->laptops = facultad->tablets = 0;
        }
    }
    return 0;
}