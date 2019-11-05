#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<int, int> l; 

int collatz(int n) {
    if (l.count(n) == 0) {
        if (n == 1)
            l[n] = 1;
        else if (n % 2 == 0)
            l[n] = collatz(n / 2) + 1;
        else 
            l[n] = collatz((3 * n) + 1) + 1;
    }  
    return l[n];
}

int main() {
    int max = 1;
    for (int i=1;i<100000;i++)
        if (l[max] < collatz(i))
            max = i;
    cout << max << endl;
}