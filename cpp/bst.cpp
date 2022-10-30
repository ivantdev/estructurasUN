#include <iostream>
#include <vector>
// #include <ctype.h>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;


template <typename T> class Node {
    public:
        T data;
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;
        Node(T x) {
            this->left = this->right = this->parent = NULL;
            this->data = x;
        }
        Node() {
            this->left = this->right = this->parent = NULL;
        }
        ~Node() {
            delete left, right, parent;
        }
};

template <typename T> class BinarySearchTree {
    public:
        Node<T>* root;

        BinarySearchTree() {
            root = NULL;
        }
        BinarySearchTree(T n) {
            root = new Node<T>;
            root->data = n;
        }

        Node<T>* find(T x, Node<T>* node) {
            if(x == node->data) {
                return node;
            }

            if(x > node->data) {
                if(node->right == NULL) return NULL;
                return this->find(x, node->right);
            }
            if(x < node->data) {
                if(node->left == NULL) return NULL;
                return this->find(x, node->left);
            }
            return NULL;
        }

        Node<T>* leftDescendant(Node<T>* node) {
            if(node->left == NULL) return node;
            return this->leftDescendant(node->left);
        }
        Node<T>* rightAncestor(Node<T>* node) {
            if(node->data < node->parent->data) return node->parent;
            else return this->rightAncestor(node->parent);
        }
        Node<T>* nextElement(Node<T>* node) {
            if(node == NULL) return NULL;
            if(node->right != NULL) {
                return this->leftDescendant(node->right);
            } else {
                return this->rightAncestor(node);
            }
        }

        vector<Node<T>*> rangeSearch(Node<T>* node, T x, T y) {
            vector<Node<T>*> arr = {};
            Node<T>* n = this->find(x, node);

            while(n->data <= y) {
                if(n->data >= x) arr.push_back(n);
                n = this->nextElement(n);
            }
            return arr;
        }

        void rangeSearch(Node<T>* node, T x, T y, vector<Node<T>*> &arr) {
            if(node->data >= x && node->data <= y) {
                arr.push_back(node);
            }
            if(node->left != NULL) {
                if(node->left->data >= x && node->left->data <= y) {
                    this->rangeSearch(node->left, x, y, &arr);
                }
            }
            if(node->right != NULL) {
                if(node->right->data >= x && node->right->data <= y) {
                    this->rangeSearch(node->right, x, y, &arr);
                }
            }

            return;
        }

        void insert(T x, Node<T>* node = NULL) {
            if(node == NULL) node = this->root;
            if(node == NULL) {
                this->root = new Node<T>(x);
                return;
            }
            if(x < node->data) {
                if(node->left == NULL) {
                    node->left = new Node<T>(x);
                    node->left->parent = node;
                    return;
                } else {
                    return insert(x, node->left);
                }
            }
            if(x > node->data) {
                if(node->right == NULL) {
                    node->right = new Node<T>(x);
                    node->right->parent = node;
                    return;
                } else {
                    return insert(x, node->right);
                }
            }
        }

        Node<T>* maximum(Node<T>* node = NULL) {
            if(node == NULL) node = this->root;
            while(node->right != NULL) {
                node = node->right;
            }
            return node;
        }

        void remove(Node<T>* node) {
            if(node == NULL) return;
            Node<T>* parent = node->parent;

            if(node->left == NULL && node->right == NULL) {
                if(parent != NULL && parent->left == node) {
                    parent->left = NULL;
                }
                if(parent != NULL && parent->right == node) {
                    parent->right = NULL;
                }
                
                delete node;
                return;
            } else if(node->left != NULL && node->right == NULL) {
                if(parent != NULL && parent->left == node) {
                    parent->left = node->left;
                }
                if(parent != NULL && parent->right == node) {
                    parent->right = node->left;
                }
                node->left = NULL;
                delete node;
                return;
            } else if(node->right != NULL && node->left == NULL) {
                if(parent != NULL && parent->left == node) {
                    parent->left = node->right;
                }
                if(parent != NULL && parent->right == node) {
                    parent->right = node->right;
                }
                Node<T>* n = node;
                node = node->right;
                n->right = NULL;
                delete n;
                return;
            } else {
                Node<T>* maxi = this->maximum(node->left);
                node->data = maxi->data;
                this->remove(maxi);
            }
        }

        void inOrder(Node<T>* node) {
            if(node->left != NULL) this->inOrder(node->left);
            cout << node->data << " ";
            if(node->right != NULL) this->inOrder(node->right);
        }


};

int main() {
    BinarySearchTree<int>* bst = new BinarySearchTree<int>();
    bst->insert(50);
    bst->insert(30);
    bst->insert(20);
    bst->insert(40);
    bst->insert(70);
    bst->insert(60);
    bst->insert(80);
    cout << "start" << endl;
    bst->inOrder(bst->root);
    cout << endl;
    Node<int>* n = bst->find(80, bst->root);
    bst->remove(n);
    bst->inOrder(bst->root);
    cout << endl;
    n = bst->find(50, bst->root);
    bst->remove(n);
    bst->inOrder(bst->root);
    cout << endl;
    cout << "root: " << bst->root->data << endl;
    n = bst->find(30, bst->root);
    bst->remove(n);
    bst->inOrder(bst->root);
    cout << endl;
    return 0;
}