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

// Linked list

int main() {
    string s;
    cin >> s;
    s = s.substr(1, s.size()-2);
    
    // Obtenemos la cadena limpia, quitamos la forma de array
    size_t pos = 0;
    string s_clean = "";
    while(pos = s.find(",") != std::string::npos) {
        s_clean = s_clean + s.substr(0, pos);
        s.erase(0, pos + 1);
    }
    s_clean = s_clean + s;

    // Creamos las listas enlazadas (conjunto P y U), luego las llenamos
    LinkedList<string>* P = new LinkedList<string>();
    LinkedList<string>* U = new LinkedList<string>();
    forn(i, s_clean.size()) {
        P->pushBack(s_clean.substr(0, i+1));
        U->pushBack(s_clean.substr(s_clean.size()-1-i, s_clean.size()));
    }

    // cout << "------------ P ------------" << endl;
    // Node<string>* cur = P->topFront();
    // while(cur->next != NULL) {
    //     cout << cur->data << endl;
    //     cur = cur->next;
    // }
    // cout << cur->data << endl;

    // cout << "------------ U ------------" << endl;
    // cur = U->topFront();
    // while(cur->next != NULL) {
    //     cout << cur->data << endl;
    //     cur = cur->next;
    // }
    // cout << cur->data << endl;

    Node<string>* cur_p = P->topFront();
    Node<string>* cur_u = U->topFront();
    forn(i, P->size) {
        if(cur_p->data == cur_u->data) {
            cout << "[";
            forn(j, cur_p->data.size()) {
                string temp = j == cur_p->data.size()-1 ? cur_p->data.substr(j, 1) + "]\n" : cur_p->data.substr(j, 1) + ",";
                cout << temp;
            }
        } else {
            if(P->find(cur_u->data)) {
                forn(j, cur_u->data.size()) {
                    string temp = j == cur_u->data.size()-1 ? cur_u->data.substr(j, 1) + "]\n" : cur_u->data.substr(j, 1) + ",";
                    cout << temp;
                }
            }

            if(U->find(cur_p->data)) {
                forn(j, cur_p->data.size()) {
                    string temp = j == cur_p->data.size()-1 ? cur_p->data.substr(j, 1) + "]\n" : cur_p->data.substr(j, 1) + ",";
                    cout << temp;
                }
            }
        }
        cur_p = cur_p->next;
        cur_u = cur_u->next;
    }
    return 0;
}