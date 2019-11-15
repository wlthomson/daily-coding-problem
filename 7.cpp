#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int count_decodings(string m) {
    unordered_map<int, int> l; 

    int k = m.length();

    l[k] = 1;
    for (int i = k-1; i>=0; i--) {
        if (m[i] == '0') {
            l[i] = 0;
        } else if (i == k-1) {
            l[i] = 1;
        } else {
            l[i] = l[i+1];
            if (stoi(m.substr(i, 2)) <= 26) {
                l[i] += l[i+2];
            }
        }
    } 
    return l[0];
}

int main() {
    cout << dec << count_decodings("111") << endl;
}

