// It is a type of complete tree.
// This binary heap will automatically resize when the heap size is over it's capacity.
#include <iostream>
#include <climits>
#include <string>

using namespace std;

class binaryHeap{
private:
    int *heap;
    int capacity;
    int heapSize;
    bool (*comparator)(int, int);   // checks if the first input is larger than the second
    void swap(int *a, int *b){
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
    void heapify(int index){
        int l = left(index);
        int r = right(index);
        int min = index;
        if (l < heapSize && comparator(heap[min], heap[l])) min = l;
        if (r < heapSize && comparator(heap[min], heap[r])) min = r;
        if (min != index) {
            swap(&heap[index], &heap[min]);
            heapify(min);
        }
    }
public:
    binaryHeap(int cpct, bool (*compare)(int, int)){
        heapSize = 0;
        heap = new int[cpct];
        capacity = cpct;
        comparator = compare;
    }
    ~binaryHeap(){
        // this is to release the memory
        delete [] heap;
    }

    int parent(int index){
        return (index-1)/2;
    }

    int left(int index) {
        return 2 * index + 1;
    }

    int right(int index){
        return 2 * index + 2;
    }

    void add(int val){
        if (heapSize == capacity){
            int *newHeap = new int[capacity*2];         // double the capacity
            capacity*=2;
            for(int i=0; i < heapSize; i++) newHeap[i] = heap[i];
            delete [] heap;
            heap = newHeap;
        }

        int i = heapSize++;
        heap[i] = val;

        while (i != 0 && comparator(heap[parent(i)],heap[i])){
            swap(&heap[i],&heap[parent(i)]);
            i = parent(i);
        }
    }

    void resetVal(int i, int newVal){
        // decrease value at i to new val
        int smaller = heap[i] > newVal;     // check if the value gets smaller
        heap[i] = newVal;
        if (smaller) {
            while (i != 0 && comparator(heap[parent(i)],heap[i])){
                swap(&heap[i],&heap[parent(i)]);
                i = parent(i);
            }
        } else {
            heapify(i);
        }
    }

    int extractMin(){
        if (heapSize < 1) {
            cerr << "No value" << endl;
            return INT_MAX;
        }
        if(heapSize == 1){
            heapSize--;
            return heap[0];
        }

        int ans = heap[0];
        heap[0] = heap[--heapSize];

        heapify(0);
        return ans;
    }

    int getMin(){
        return heap[0];
    }

    void deleteVal(int index){
        resetVal(index, INT_MIN);
        extractMin();
    }

    string toString(){
        string ans = "[";
        for(int i=0; i < heapSize; i++) ans += to_string(heap[i]) +", ";
        return ans.substr(0, ans.length()-2) +"]";
    }
};

bool comparator(int a, int b){
    return a > b;
}

int main(){
    binaryHeap bh = binaryHeap(10, comparator);
    bh.add(2);
    bh.add(3);
    bh.add(5);
    bh.add(7);
    bh.add(0);
    bh.add(4);
    bh.add(6);
    bh.add(8);
    bh.add(1);

    cout << bh.toString() << endl;
    cout  << bh.extractMin() << " is min now" << endl;

    cout << bh.toString() << endl;
    cout << bh.extractMin() << " is min now" << endl;

    cout << bh.toString() << endl;
    cout <<  bh.extractMin() << " is min now" << endl;

    cout << bh.toString() << endl;
    bh.deleteVal(0);
    cout << bh.toString() << endl;
    cout <<  bh.getMin() << " is min now" << endl;

    bh.add(114);
    bh.add(26);
    bh.add(38);
    bh.add(41);
    bh.add(115);
    bh.add(216);
    bh.add(338);
    bh.add(451);
    bh.add(21);
    bh.add(33);
    bh.add(45);
    cout << bh.toString() << endl;

    return 0;
}