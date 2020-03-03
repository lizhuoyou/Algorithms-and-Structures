#include <iostream>
#include <string>

using namespace std;

void heapify(int heapArr[], int size, int index, bool (*comparator)(int, int)){
    int l = 2 * index + 1;
    int r = 2 * index + 2;
    int min = index;
    if (l < size && comparator(heapArr[min], heapArr[l])) min = l;
    if (r < size && comparator(heapArr[min], heapArr[r])) min = r;
    if (min != index) {
        swap(heapArr[index], heapArr[min]);
        heapify( heapArr, size, min, comparator);
    }
}

//
void heapSort(int arr[], int size, bool (*comparator)(int, int)){
    // initialize heap by let all children larger than parents
    int p;
    for(int i = 1; i < size; i++){
        p  = i;
        while (p!=0 && comparator(arr[(p-1)/2], arr[p])){
            swap(arr[(p-1)/2],arr[p]);
            p = (p-1)/2;
        }
    }

    for (int i = 1; i < size ; i++) {
        swap(arr[0],arr[size-i]);
        heapify(arr, size-i, 0, comparator);
    }

    for(int i = 0; i < size/2; i++) swap(arr[i],arr[size-i-1]);
}


bool comparator(int a, int b){
    return a > b;
}

string arrToString(int arr[], int size){
    string ans = "[";
    for(int i=0; i < size; i++) ans += to_string(arr[i]) +", ";
    return ans.substr(0, ans.length()-2) +"]";
}

int main(){
    int arr[] = {1, 5, 2, 6, 3, 7, 9, 4, 8, 0};
    heapSort(arr, 10, comparator);
    cout << arrToString(arr, 10) << endl;

    return 0;
}