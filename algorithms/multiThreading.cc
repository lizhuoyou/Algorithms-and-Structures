#include <iostream>
#include <thread>
#include <string>
using namespace std;

void foo(string *a){
    for (int i =1 ; i< 10001; i++){
        *a += " " + to_string(i);
    }
}

int main(){
    string a;
    string b;
    string c;
    auto timeS = chrono::steady_clock::now();
    thread td0(foo, &a);
    thread td1(foo, &b);
    thread td2(foo, &c);
    td1.join();
    td2.join();
    td0.join();
    cout << "a, b, c are:" << a << " " << b << " " << c << endl;
    auto timeE = chrono::steady_clock::now();
    double timeDiff = chrono::duration<double, milli>(timeE-timeS).count();
    cout << "Multi threading time: " << timeDiff << endl;

    string d;
    string e;
    string f;
    auto timeSs = chrono::steady_clock::now();
    foo(&d);
    foo(&e);
    foo(&f);
    cout << "a, b, c are:" << a << " " << b << " " << c << endl;
    auto timeEe = chrono::steady_clock::now();
    double timeDifff = chrono::duration<double, milli>(timeEe-timeSs).count();
    cout << "Normal time: " << timeDifff << endl;

    return 0;
}