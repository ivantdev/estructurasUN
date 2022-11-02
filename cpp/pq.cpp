#include <iostream>
#include <vector>
#include "node.h"

// #include <ctype.h>

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)


template<typename T> class PriorityQueue {
    private:
        int parent(int i) {
            return (i/2);
        }
        int leftChild(int i) {
            return (i*2);
        }
        int rightChild(int i) {
            return (i*2 + 1);
        }
    public:
        vector<T> queue;
        PriorityQueue(T x) {
            this->queue = {};
            this->queue.push_back(x);
        }
        PriorityQueue() {
            this->queue = {};
        }

        T getMax() {
            return (this->queue.size() > 0) ? this->queue[0] : 0;
        }

        T extractMax() {
            T result = this->queue[0];
            this->queue[0] = this->queue[this->queue.size() - 1];
            this->queue.pop_back();
            this->shiftDown(1);
            return result;
        }

        void shiftUp(int i) {
            while (i>1 && this->queue[this->parent(i) - 1] < this->queue[i - 1]) {
                T aux = queue[this->parent(i) - 1];
                queue[this->parent(i) - 1] = this->queue[i - 1];
                this->queue[i - 1] = aux;
                i = this->parent(i);
            }

        }

        void shiftDown(int i) {
            int maxIdx = i;
            int size = this->queue.size();

            int left = this->leftChild(i);
            if (left <= size && this->queue[left - 1] > this->queue[maxIdx - 1]) maxIdx = left;

            int right = this->rightChild(i);
            if (right <= size && this->queue[right - 1] > this->queue[maxIdx - 1]) maxIdx = right;

            if (i != maxIdx) {
                T aux = this->queue[i - 1];
                this->queue[i - 1] = this->queue[maxIdx - 1];
                this->queue[maxIdx - 1] = aux;

                return shiftDown(maxIdx);
            }

        }

        void insert(T x) {
            this->queue.push_back(x);
            shiftUp(this->queue.size());
        }

        void changePriority(int i, int p) {
            int oldp = this->queue[i - 1];
            this->queue[i - 1] = p;
            if(p > oldp) this->shiftUp(i);
            else this->shiftDown(i);
        }

        void remove(int i) {
            this->queue[i - 1] = this->queue[0];
            this->shiftUp(i);
            this->extractMax();
        }
};


int main() {
    PriorityQueue<int>* pq = new PriorityQueue<int>();
    pq->insert(42);
    pq->insert(29);
    pq->insert(18);
    pq->insert(14);
    pq->insert(7);
    pq->insert(18);
    pq->insert(12);
    pq->insert(11);

    forn(i, pq->queue.size()){
        cout << pq->queue[i] << " ";
    }
    cout << endl;
    pq->insert(30);
        forn(i, pq->queue.size()){
        cout << pq->queue[i] << " ";
    }
    cout << endl;
    return 0;
}