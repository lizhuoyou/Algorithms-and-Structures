#include <iostream>
#include <string>
#include <list>

using namespace std;

class hashTable{
private:
    int size, tableSize;
    double maxLoad;
    list<int> *table{};

    void clear(int n){
        // it clears and resize the table
        delete [] table;
        table = new list<int>[n];
    }

    void resize() {
        // resize the table to increase its spots which allows more values to be entered.
        auto *lst = new list<int>;
        for(int i = 0; i < tableSize; i++){
            list<int> l = table[i];
            while(!l.empty()){
                lst->push_back(l.front());
                l.pop_front();
            }
        }

        size = 0;
        tableSize *= 2;        // update the full size of the table
        clear(tableSize );       // clear and increase the size of the table to hold more values.
        while(!lst->empty()){
            add(lst->front());
            lst->pop_front();
        }

        delete lst;
    }

public:
    hashTable(){
        size = 0;
        tableSize = 10;
        maxLoad = 0.6;
        clear(10);
    }

    int hashFunction(int val){
        if(val < 0) val *= -1;
        return val % tableSize;
    }

    void add(int val){
        // add a value to the table.
        int pos = hashFunction(val);
        list<int> *lst = &table[pos];
        lst->push_back(val);
        size++;
        if (getLoad() > maxLoad) {     // check if the load amount is over max percent
            resize();
        }
    }

    double getLoad(){
        return (double) size / (double) tableSize;
    }

    void setMaxLoad(double percent){
        // set the max load of the table, wich is restricted from 0.2 to 0.8
        if (percent >= 0.1 && percent <= 0.8) {     // check if the new maxLoad is valid
            while(getLoad()>maxLoad) resize();
            maxLoad = percent;
        }
    }

    bool contains(int val){
        int index = hashFunction(val);
        list<int>::iterator it;
        for (it = table[index].begin(); it != table[index].end(); ++it) {
            if(val == *it) return true;
        }
        return false;
    }

    void remove(int val){
        int index = hashFunction(val);
        list<int>::iterator it;
        for (it = table[index].begin(); it != table[index].end(); ++it) {
            if(val == *it) {
                table[index].remove(val);
                size--;
                return;
            }
        }
    }

    string toString(){
        string ans = "[";
        for(int i = 0; i < tableSize; i++){
            list<int> lst = table[i];
            while(!lst.empty()){
                ans += to_string(lst.front()) + ", ";
                lst.pop_front();
            }
        }
        return ans.substr(0, ans.length()-2)+"]";
    }
};

int main(){
    hashTable hashT = hashTable();
    hashT.add(0);
    hashT.add(11);
    hashT.add(13);
    hashT.add(14);
    hashT.add(12);
    hashT.add(15);
    cout << hashT.toString() << endl;
    hashT.add(10);
    hashT.add(1);
    hashT.add(3);
    hashT.add(4);
    hashT.add(2);
    hashT.add(7);
    cout << hashT.toString() << endl;
    if(hashT.contains(7)) cout << "It contains " << 7 << endl;
    hashT.remove(7);
    hashT.setMaxLoad(0.2);
    cout << hashT.toString() << endl;
    return 0;
}