#include <iostream>
#include <vector>
// #include <ctype.h>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;


int parent(int i) {
    return (i/2);
}
int leftChild(int i) {
    return (i*2);
}
int rightChild(int i) {
    return (i*2 + 1);
}

void Heapify(vector<int> &arr, int i, int size) {
    int maxIdx = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if(left <= size && arr[left - 1] > arr[maxIdx - 1]) maxIdx = left;
    if(right <= size && arr[right - 1] > arr[maxIdx - 1]) maxIdx = right;

    if(i != maxIdx) {
        int aux = arr[i - 1];
        arr[i - 1] = arr[maxIdx - 1];
        arr[maxIdx - 1]  = aux;

        Heapify(arr, maxIdx, size);
    }
}

void HeapSort(vector<int> &arr) {
    int size = arr.size();
    dforsn(i, 1, size/2){
        Heapify(arr, i, size);
    }

    dforsn(i, 0, size) {
        int aux = arr[0];
        arr[0] = arr[i];
        arr[i] = aux;

        Heapify(arr, 1, i);
    }
};

int main() {
    vector<int> array = {45, 48, 96, 88, 13, 100, 90, 58, 71, 97, 64, 21, 79, 67, 19, 2, 44, 30, 61, 8, 77, 92, 85, 28, 12, 81};
    cout << "antes \n";
    forn(i, array.size()) {
        cout << array[i] << " ";
    }
    cout << endl;

    HeapSort(array);

    cout << "\ndespues \n";
    forn(i, array.size()) {
        cout << array[i] << " ";
    }
    cout << endl;
    return 0;
}