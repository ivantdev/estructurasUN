#include <iostream>
#include <vector>
#include "heapsort.h"

#define forn(i,n) for(int i=0;i<int(n);i++)
#define forsn(i,s,n) for(int i=int(s); i<int(n);i++)
#define forcn(i,c,n) for(int i=0;i<int(n) && c;i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

using namespace std;


int main() {
    vector<double> array = {4.6680027, 4.6676407, 4.6672853, 4.6669514, 4.6665492, 4.6665139, 4.6664867, 4.6664213, 4.66639, 4.6663566};
    cout << "antes \n";
    forn(i, array.size()) {
        cout << array[i] << " ";
    }
    cout << endl;

    HeapSort<double>(array);

    cout << "\ndespues \n";
    forn(i, array.size()) {
        printf("%.7f ", array[i]);
    }
    cout << endl;
    return 0;
}

