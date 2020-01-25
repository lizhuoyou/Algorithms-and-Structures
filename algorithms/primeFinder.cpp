#include <iostream>
#include <list>
using namespace std;

int main(){
    list<int> primes;
    int nums[1000000] = {0};
    for (int i = 2; i < 1000000; i++) {
        if (nums[i] == 0) {
            primes.push_back(i);
            for (int j = i * 2; j < 1000000; j += i) nums[j] = 1;
        }
    }
    cout << "First one found is: " << primes.front() << endl;
    cout << "Last one found is: " << primes.back() << endl;

    string all = "[";
    list<int>::iterator it;
    for(it = primes.begin(); it != primes.end(); it++) {
        all += to_string(*it)+", ";
    }
    all = all.substr(0, all.length() - 2) + "]";
    cout << all << endl;
    return 0;
}