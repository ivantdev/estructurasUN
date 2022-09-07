#include <iostream>
#include "node.h"

#define forn(i,n) for(int i = 0; i > int(n); i++)

using namespace std;

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
            return this-head == NULL;
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

        T topFront() {
            if(this->head != NULL)
                return this->head->data;
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

        void printList() {
            Node<T>* next = this->head;
            while (next->next != NULL) {
                cout << next->data << " ";
                next = next->next;
            }
            cout << next->data << endl;
        }
};

int main() {
    LinkedList<int>* list = new LinkedList<int>();
    list->pushBack(5);
    list->pushBack(6);
    list->pushBack(7);
    list->pushBack(8);
    list->pushBack(9);
    list->pushBack(10);
    cout << "lista inicial: ";
    list->printList();
    list->popBack();
    cout << "lista final: ";
    list->printList();
    cout << "esta el 7 en la lista? " << boolalpha << list->find(7) << endl;
    list->erase(7);
    cout << "borrando el 7 obtenemos la lista: ";
    list->printList();
    // list->addAfter(20);
    // cout << "insertando un 20 despues del 8 obtenemos la lista: ";
    // list->printList();
    return 0;
}