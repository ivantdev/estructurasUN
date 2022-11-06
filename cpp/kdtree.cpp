#include <iostream>
#include <vector>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;

template<typename T> class Node {
    public:
        vector<T> data;
        Node<T>* left;
        Node<T>* right;

        Node(vector<T> &arr) {
            this->data = arr;
            this->left = this->right = NULL;
        }
};

int parent(int i) {
    return ((i-1)/2);
}
int leftChild(int i) {
    return (i*2 + 1);
}
int rightChild(int i) {
    return (i*2 + 2);
}

template<typename T> void Heapify(vector<vector<T>> &arr, int i, int size, int k) {
    int maxIdx = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if(left < size && arr[left][k] > arr[maxIdx][k]) maxIdx = left;
    if(right < size && arr[right][k] > arr[maxIdx][k]) maxIdx = right;

    if(i != maxIdx) {
        vector<T> aux = arr[i];
        arr[i] = arr[maxIdx];
        arr[maxIdx]  = aux;

        Heapify<T>(arr, maxIdx, size, k);
    }
}

template<typename T>void HeapSort(vector<vector<T>> &arr, int k) {
    dforsn(i, 0, (arr.size()/2)){
        Heapify<T>(arr, i, arr.size(), k);
    }

    dforsn(i, 0, arr.size()) {
        vector<T> aux = arr[0];
        arr[0] = arr[i];
        arr[i] = aux;

        Heapify<T>(arr, 0, i, k);
    }
};


template<typename T> class KDTree {
    public: 
        Node<T>* root;
    KDTree(vector<vector<T>> &array) {
        this->root = this->genRoot(array, 0);
    }

    Node<T>* genRoot(vector<vector<T>> &arr, int k) {
        if(arr.size() == 0) return NULL;
        if(arr.size() == 1) return new Node<T>(arr[0]);
        if(arr.size() == 2) {
            int imax = 1, imin = 0;
            if(arr[0][k] < arr[1][k]) {
                imax = 0;
                imin = 1;
            }
            Node<T>* root = new Node<T>(arr[imax]);
            if(arr[0][(k+1)%2] > arr[1][(k+1)%2]) {
                root->left = new Node<T>(arr[imin]);
            } else {
                root->right = new Node<T>(arr[imin]);
            }
            return root;
        }

        HeapSort<T>(arr, k);

        int i = (arr.size()%2 == 0) ? (arr.size()/2) - 1: (arr.size()/2);

        Node<T>* root = new Node<T>(arr[i]);
        vector<vector<T>> left = {arr.begin(), arr.begin() + i};
        vector<vector<T>> right = {arr.begin() + i + 1, arr.end() };
        root->left = genRoot(left, (k+1)%2);
        root->right = genRoot(right, (k+1)%2);
        return root;
    }

    Node<T>* closest(vector<T> &target, Node<T>* node_a, Node<T>* node_b) {
        double x = (target[0]-node_a->data[0]);
        x = x*x;
        double y = (target[1]-node_a->data[1]);
        y = y*y;
        double target_a = x+y;

        x = (target[0]-node_b->data[0]);
        x = x*x;
        y = (target[1]-node_b->data[1]);
        y = y*y;
        double target_b = x+y;
        // printf("target: %.7f %.7f \nn.a: %.7f %.7f to target %.16f\nn.b: %.7f %.7f to target %.16f\n", target[0], target[1], node_a->data[0], node_a->data[1], target_a, node_b->data[0], node_b->data[1], target_b);

        if(target_a < target_b) return node_a;
        else return node_b;
    }

    double distNodes(vector<T> &a, Node<T>* b) {
        double x = (a[0]-b->data[0]);
        x = x*x;
        double y = (a[1]-b->data[1]);
        y = y*y;
        return x+y;
    }

    Node<T>* nearestNeighbor(Node<T>* node, vector<T> &target, int k = 0) {
        if(node == NULL) return NULL;
        Node<T>* node_a;
        Node<T>* node_b;
        if(target[k] < node->data[k]) {
            node_a = node->left;
            node_b = node->right;
        } else {
            node_a = node->right;
            node_b = node->left;
        }

        Node<T>* node_c = this->nearestNeighbor(node_a, target, (k+1)%2);
        Node<T>* best = (node_c != NULL) ? this->closest(target, node, node_c) : node;

        double r = distNodes(target, best);
        double rc = target[k] - node->data[k];

        printf("r: %.16f rc: %.16f\n", r, rc*rc);

        // if(node != NULL) {
        //     cout << "nodo r: " << node->data[0] << " " << node->data[1] << " " << node->data[2] << endl;
        // }
        // if(node_a != NULL) {
        //     cout << "nodo a: " << node_a->data[0] << " " << node_a->data[1] << " " << node_a->data[2] << endl;
        // }
        // if(node_b != NULL) {
        //     cout << "nodo b: " << node_b->data[0] << " " << node_b->data[1] << " " << node_b->data[2] << endl;
        // }

        if(r >= (rc*rc)) {
            Node<T>* temp = this->nearestNeighbor(node_b, target, (k+1)%2);
            best = (temp != NULL) ? closest(target, best, temp) : best;
        }

        return best;
    }

    // void niveles(Node<T>* node, int n) {
    //     if(node == NULL) return;
    //     cout << "nivel: " << n << endl;
    //     printf("lat: %d lon: %d id: %d\n", node->data[0], node->data[1], node->data[2]);
    //     this->niveles(node->left, n+1);
    //     this->niveles(node->right, n+1);
    // }

    int height(Node<T>* node) {
        if(node == NULL) return 0;
        return 1 + max(this->height(node->left), this->height(node->right));
    }
};

// int main() {
//     vector<vector<double>> nodes;
//     string s;
//     while(getline(cin, s)) {
//         vector<double> arr{};
//         double id = stod(s.substr(0, s.find(" ")));
//         s.erase(0, s.find(" ")+1);
//         double lat = stod(s.substr(0, s.find(" ")));
//         s.erase(0, s.find(" ")+1);
//         double lng = stod(s.substr(0, s.find(" ")));
//         s.erase(0, s.find(" ")+1);
//         arr.push_back(lat);
//         arr.push_back(lng);
//         arr.push_back(id);
//         nodes.push_back(arr);
//     }


//     KDTree<double>* kdtree = new KDTree<double>(nodes);
//     printf("root: %.7f %.7f\n",kdtree->root->data[0], kdtree->root->data[1]);
//     cout << "height: " << kdtree->height(kdtree->root) << endl;
//     vector<double> target{4.7233639, -74.03354220000001};
//     Node<double>* result = kdtree->nearestNeighbor(kdtree->root, target);
//     printf("lat: %.7f lng: %.7f\n", result->data[0], result->data[1]);
//     return 0;
// }