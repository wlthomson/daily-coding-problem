#include <iostream>
#include <vector>

using namespace std;

// Recursion, no memoisation.
//
// Time: O(2^n)
// Space: O(n)
int steps_rc(const int n) {
    if (n <= 2) return n;
    return steps_rc(n-1) + steps_rc(n-2);
}

// DP, memoises all computations.
//
// Time: O(n)
// Space: O(n)
int steps_dp(const int n) {
    int arr[n+1];
    for (int i=0; i<=n; i++) {
        switch (i) {
            case 0: { arr[i] = 0; break; }
            case 1: { arr[i] = 1; break; }
            case 2: { arr[i] = 2; break; }
            default: { arr[i] = arr[i-1] + arr[i-2]; }
        }
    }
    return arr[n];
}

int main() {
    const int n = 4;
    cout << steps_rc(n) << endl;
    cout << steps_dp(n) << endl;
}
