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
        int height;
        Node(T x) {
            this->left = this->right = this->parent = NULL;
            this->data = x;
            this->height = 1;
        }
        Node() {
            this->left = this->right = this->parent = NULL;
        }
        ~Node() {
            delete left, right, parent;
        }
};

template <typename T> class BinarySearchTreeAVL {
    public:
        Node<T>* root;

        BinarySearchTreeAVL() {
            root = NULL;
        }
        BinarySearchTreeAVL(T n) {
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

        void rotateLeft(Node<T>* node) {
            if(node->parent == NULL) this->root = node->right;
            else {
                if(node->parent->right == node) {
                    node->parent->right = node->right;
                } else {
                    node->parent->left = node->right;
                }
            }

            node->right->parent = node->parent;
            node->parent = node->right;
            node->right = node->right->left;
            if(node->right != NULL) node->right->parent = node;
            node->parent->left = node;
        }

        void rotateRight(Node<T>* node) {
            if(node->parent == NULL) this->root = node->left;
            else {
                if(node->parent->left == node) {
                    node->parent->left = node->left;
                } else {
                    node->parent->right = node->left;
                }
            }

            node->left->parent = node->parent;
            node->parent = node->left;
            node->left = node->left->right;
            if(node->left != NULL) node->left->parent = node;
            node->parent->right = node;
        }

        void rotateLeftRight(Node<T>* node) {
            this->rotateLeft(node->left);
            // node->left->right->parent = node;
            // node->left->parent = node->left->right;

            // node->left->right = node->left->right->left;

            // if(node->left->right != NULL) node->left->right->parent = node->left;

            // node->left->parent->left = node->left;
            // node->left = node->left->parent;

            this->rotateRight(node);
        }

        void rotateRightLeft(Node<T>* node) {
            this->rotateRight(node->right);
            // node->right->left->parent = node;
            // node->right->parent = node->right->left;

            // node->right->left = node->right->left->right;

            // if(node->right->left != NULL) node->right->left->parent = node->right;

            // node->right->parent->right = node->right;
            // node->right = node->right->parent;

            this->rotateLeft(node);
        }

        void rebalance(Node<T>* node) {
            Node<T>* parent = node->parent;
            this->adjustHeight(parent);
            int balance = this->getBalance(node);
            int balance_left = this->getBalance(node->left);
            int balance_right = this->getBalance(node->right);
            if(balance < -1) {
                if(balance_right == -1) {
                    this->rotateLeft(node);
                } else if(balance_right == 1) {
                    this->rotateRightLeft(node);
                    this->adjustHeight(node->parent);
                }
            } else if(balance > 1) {
                if(balance_left == 1) {
                    this->rotateRight(node);
                } else if(balance_left == -1){
                    this->rotateLeftRight(node);
                    this->adjustHeight(node->parent);
                }
            }
            if(parent != NULL) return this->rebalance(parent);
        }

        int getBalance(Node<T>* node) {
            if(node == NULL) return 0;
            int left;
            int right;
            if(node->left == NULL) left = 0;
            else left = node->left->height;

            if(node->right == NULL) right = 0;
            else right = node->right->height;

            return left - right;
        }

        int adjustHeight(Node<T>* node) {
            if(node == NULL) return 0;
            node->height = 1 + max(this->adjustHeight(node->left), this->adjustHeight(node->right));
            return node->height;
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

        void insertAVL(T x, Node<T>* node = NULL) {
            this->insert(x, node);
            Node<T>* n = this->find(x, this->root);
            this->rebalance(n);
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
                if(parent == NULL) this->root = NULL;
                if(parent != NULL && parent->left == node) {
                    parent->left = NULL;
                }
                if(parent != NULL && parent->right == node) {
                    parent->right = NULL;
                }
                
                delete node;
                return;
            } else if(node->left != NULL && node->right == NULL) {
                if(parent == NULL) this->root = node->left;
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
                if(parent == NULL) this->root = node->right;
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
            if(parent != NULL) return this->rebalance(parent);
        }

        void inOrder(Node<T>* node) {
            if(node->left != NULL) this->inOrder(node->left);
            cout << node->data << " ";
            if(node->right != NULL) this->inOrder(node->right);
        }


};

// int main() {
//     BinarySearchTreeAVL<int>* bst = new BinarySearchTreeAVL<int>();
//     bst->insertAVL(92);
//     bst->insertAVL(32);
//     bst->insertAVL(99);
//     bst->insertAVL(72);
//     bst->insertAVL(95);
//     bst->insertAVL(46);
//     bst->insertAVL(4);
//     bst->insertAVL(98);
//     bst->insertAVL(9);
//     bst->insertAVL(30);
//     bst->insertAVL(77);
//     bst->insertAVL(36);
//     bst->insertAVL(49);
//     bst->insertAVL(42);
//     bst->insertAVL(11);
//     bst->insertAVL(74);
//     bst->insertAVL(15);
//     bst->insertAVL(67);
//     bst->insertAVL(87);
//     bst->insertAVL(96);
//     bst->insertAVL(54);
//     bst->insertAVL(57);
//     bst->insertAVL(93);
//     bst->insertAVL(31);
//     bst->insertAVL(50);
//     bst->insertAVL(85);
//     bst->insertAVL(76);
//     bst->insertAVL(90);
//     bst->insertAVL(16);
//     bst->insertAVL(55);
//     bst->insertAVL(10);
//     bst->insertAVL(89);
//     bst->insertAVL(79);
//     bst->insertAVL(52);
//     bst->insertAVL(24);
//     bst->insertAVL(70);
//     bst->insertAVL(73);
//     bst->insertAVL(20);
//     bst->insertAVL(12);
//     bst->insertAVL(64);
//     bst->insertAVL(45);
//     bst->insertAVL(100);
//     bst->insertAVL(51);
//     bst->insertAVL(56);
//     bst->insertAVL(71);
//     bst->insertAVL(59);
//     bst->insertAVL(47);
//     bst->insertAVL(17);
//     bst->insertAVL(3);
//     bst->insertAVL(13);
//     bst->insertAVL(88);
//     bst->insertAVL(97);
//     bst->insertAVL(83);
//     bst->insertAVL(75);
//     bst->insertAVL(61);
//     bst->insertAVL(44);
//     bst->insertAVL(94);
//     bst->insertAVL(78);
//     bst->insertAVL(18);
//     bst->insertAVL(60);
//     bst->insertAVL(62);
//     bst->insertAVL(35);
//     bst->insertAVL(86);
//     bst->insertAVL(23);
//     bst->insertAVL(27);
//     bst->insertAVL(6);
//     bst->insertAVL(25);
//     bst->insertAVL(84);
//     bst->insertAVL(38);
//     bst->insertAVL(8);
//     bst->insertAVL(37);
//     bst->insertAVL(63);
//     bst->insertAVL(91);
//     bst->insertAVL(28);
//     bst->insertAVL(1);
//     bst->insertAVL(80);
//     bst->insertAVL(29);
//     bst->insertAVL(7);
//     bst->insertAVL(69);
//     bst->insertAVL(39);
//     bst->insertAVL(34);
//     bst->insertAVL(33);
//     bst->insertAVL(68);
//     bst->insertAVL(19);
//     bst->insertAVL(65);
//     bst->insertAVL(43);
//     bst->insertAVL(2);
//     bst->insertAVL(48);
//     bst->insertAVL(21);
//     bst->insertAVL(14);
//     bst->insertAVL(81);
//     bst->insertAVL(40);
//     bst->insertAVL(41);
//     bst->insertAVL(22);
//     bst->insertAVL(58);
//     bst->insertAVL(5);
//     bst->insertAVL(26);
//     bst->insertAVL(53);
//     bst->insertAVL(82);
//     bst->insertAVL(66);

//     cout << "root: " << bst->root->data << endl;
//     bst->remove(bst->root);
//     bst->inOrder(bst->root);
//     cout << endl;
//     cout << "root: " << bst->root->data << endl;

//     return 0;
// }
