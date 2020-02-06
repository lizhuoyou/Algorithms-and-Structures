// this file is not bug free yet!
// sometimes it gives bugs with answers!
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RSA{
    int p;
    int q;
    int n;
    int e;
    int d;
    int gcd(int a, int b) {
        while (b != 0) {
            int r = a%b;
            a = b;
            b = r;
        }
        return a;
    }
public:
    RSA(int dataMax){
        if(dataMax > 988207){
            cerr << "\nError, the data is too big to fit in RSA." << endl;
            exit(1);
        }
        p = 0;
        q = 0;
        vector<int> primes;
        int nums[1000];
        for (int i = 2; i < 1000; i++) nums[i] = 1;
        for (int i = 2; i < 1000; i++) {
            if (nums[i] == 1) {
                primes.push_back(i);
                for (int j = i * 2; j < 1000; j += i) nums[j] = 0;
            }
        }

        int size = primes.size();
        srand(time(nullptr));
        p = primes[rand() % size];
        if (primes[size - 1] < dataMax / p) {
            for (int i = 0; i < size; i++) {
                if (primes[i] >= dataMax / primes[size - 1]) {
                    p = primes[i + rand()%(size-i)];
                    break;
                }
            }
            q = primes[size - 1];
        } else {
            for (int i = 0; i < size; i++) {
                if (primes[i] >= dataMax / p) {
                    q = primes[i + rand()%(size-i)];
                    while (q == p) {
                        q = primes[i + rand()%(size-i)];
                    }
                    break;
                }
            }
        }

        n = p * q;
        int alpha = (p-1)*(q-1);
        for (int i = 2; i < alpha; i++) {
            if (gcd(i, alpha) == 1) {
                e = i;
                break;
            }
        }
        for (int i = 2; i < alpha; i++) {
            if (i * e % alpha == 1) {
                d = i;
                break;
            }
        }
    }

    pair<int, int> getPublicKeys(){
        pair<int, int> ans = {e,n};
        return ans;
    }

    int encrypt(int M, int eVal, int nVal){
        // can used to encrypt message based on received public keys
        long long C = 1;
        while(eVal > 0){
            C %= nVal;
            C *= (M % nVal);
            eVal--;
        }
        return (int) (C % nVal);
    }

    int decrypt(int encrytData){
        // can used to decrypt data encrypted by this object's public keys.
        long long R = 1, dCopy = d;
        while(dCopy > 0){
            R %= n;
            R *= encrytData % n;
            dCopy--;
        }

        return (int)(R % n);
    }
};

int main(){
    RSA myRSA = RSA(100);
    pair<int, int> keys = myRSA.getPublicKeys();
    int C = myRSA.encrypt(10, keys.first, keys.second);
    cout << myRSA.decrypt(C) << endl;
    return 0;
}