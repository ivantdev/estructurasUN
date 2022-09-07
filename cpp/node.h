#include <iostream>

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
};