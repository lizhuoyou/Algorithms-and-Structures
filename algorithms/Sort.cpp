// a collection of sorting algorithms
#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n, int (*compare)(int, int)){
    for(int i = 0; i < n; i++){
        for(int j = 1; j < n-i; j++){
            if(compare(arr[j-1], arr[j]) > 0){
                arr[j-1] ^= arr[j];
                arr[j] ^= arr[j-1];
                arr[j-1] ^= arr[j];
            }
        }
    }
}

void insertSort(int arr[], int n, int (*compare)(int, int)){
    for(int i = 1; i < n; i++){
        int copy = i;
        while (copy > 0 && compare(arr[copy-1], arr[copy]) > 0) {
            arr[copy] ^= arr[copy - 1];
            arr[copy - 1] ^= arr[copy];
            arr[copy--] ^= arr[copy-1];
        }
    }
}


void mergeSortReal(int arr[], int temp[], int n, int (*compare)(int, int)){
    if(n < 2){
        return;
    }

    int middle = n/2;

    mergeSortReal(arr, temp, middle,compare);
    mergeSortReal(arr + middle, temp, n - middle, compare);

    int i = 0, j = middle, k = 0;
    while(i < middle && j < n){
        if(compare(arr[i], arr[j]) < 0) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while(i < middle) temp[k++] = arr[i++];
    while(j < n) temp[k++] = arr[j++];
    for(int a = 0; a < n; a++) arr[a] = temp[a];
}

void mergeSort(int arr[], int n, int (*compare)(int, int)){
    int *temp = (int*)malloc(sizeof(int)*n);
    mergeSortReal(arr, temp, n, compare);
    free(temp);
}

void quickSort(int arr[], int n, int (*compare)(int, int)){
    if(n < 2){
        return;
    }
    int pivot = 0;
    for(int i = 1; i < n; i ++){
        if(compare(arr[0],arr[i]) > 0){
            int a = arr[++pivot];
            arr[pivot] = arr[i];
            arr[i] = a;
        }
    }
    int a = arr[pivot];
    arr[pivot] = arr[0];
    arr[0] = a;
    quickSort(arr, pivot, compare);
    quickSort(arr + pivot + 1, n - pivot - 1, compare);
}

int compare(int a, int b){
    return a - b;
}

void printArray(int arr[], int n){
    cout << "[";
    for(int i = 0; i < n-1; i++) cout << arr[i] << ", ";
    cout << arr[n-1] << "]\n";
}

int main(){
    int arr0[] = {2, 34, 435, 435, 3, 4, 49, 5, 7, 675, 7, 4543};
    int arr1[] = {2, 34, 435, 435, 3, 4, 49, 5, 7, 675, 7, 4543};
    int arr2[] = {2, 34, 435, 435, 3, 4, 49, 5, 7, 675, 7, 4543};
    int arr3[] = {2, 34, 435, 435, 3, 4, 49, 5, 7, 675, 7, 4543};

    int size = sizeof(arr0) / sizeof(arr0[0]);
    bubbleSort(arr0, size, compare);
    insertSort(arr1, size, compare);
    mergeSort(arr2, size, compare);
    quickSort(arr3, size, compare);

    printArray(arr0, size);
    printArray(arr1, size);
    printArray(arr2, size);
    printArray(arr3, size);

    return 0;
}