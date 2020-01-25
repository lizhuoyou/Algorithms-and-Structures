#include <iostream>

using namespace std;


int bSearch(int v[], int size, int num){
    int index = size/2;
    int boundS = 0;
    int boundB = size-1;
    while (v[index] != num) {
        if(boundB == boundS){
            cerr << "\nError, no such value.\n";
            exit(1);
        }
        if(v[index] < num){
            boundS = index;
            index += (boundB - index) / 2;
        } else{
            boundB = index;
            index -= (index - boundS) / 2;
        }
    }
    return index;
}

int main(){
    int a[5] = {1, 2, 3, 4, 5};
    cout << bSearch(a, 5, 3) << endl;
    return 0;
}