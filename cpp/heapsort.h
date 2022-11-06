#include <vector>


#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;

int parent(int i) {
    return ((i-1)/2);
}
int leftChild(int i) {
    return (i*2 + 1);
}
int rightChild(int i) {
    return (i*2 + 2);
}

template<typename T> void Heapify(vector<T> &arr, int i, int size) {
    int maxIdx = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if(left < size && arr[left] > arr[maxIdx]) maxIdx = left;
    if(right < size && arr[right] > arr[maxIdx]) maxIdx = right;

    if(i != maxIdx) {
        T aux = arr[i];
        arr[i] = arr[maxIdx];
        arr[maxIdx]  = aux;

        Heapify(arr, maxIdx, size);
    }
}

template<typename T>void HeapSort(vector<T> &arr) {
    int size = arr.size();
    dforsn(i, 0, size/2){
        Heapify(arr, i, size);
    }

    dforsn(i, 0, size) {
        T aux = arr[0];
        arr[0] = arr[i];
        arr[i] = aux;

        Heapify(arr, 0, i);
    }

};