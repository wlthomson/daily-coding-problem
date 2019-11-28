#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int max(vector<int> arr) {
    return *max_element(arr.begin(), arr.end());
}

// Recursion, no memoisation.
//
// Time: O(2^n)
// Space: O(n)
int __max_non_adjacent(const vector<int> arr) {
    int n = arr.size();
    int max_exclude_next, max_include_next;
    switch (n) {
        case 0: { max_exclude_next = 0; max_include_next = 0; break; }
        case 1: { max_exclude_next = arr[0]; max_include_next = 0; break; }
        case 2: { max_exclude_next = arr[0]; max_include_next = arr[1]; break; }
        default: {
            vector<int>::const_iterator first = arr.begin()+1;
            vector<int>::const_iterator second = arr.begin()+2;
            vector<int>::const_iterator end = arr.end();
            max_exclude_next = arr[0] + __max_non_adjacent(vector<int>(second, end));
            max_include_next = __max_non_adjacent(vector<int>(first, end));
        }
    }
    return max(max_exclude_next, max_include_next);
}

// DP, memoises all computations.
//
// Time: O(n)
// Space: O(n)
int _max_non_adjacent(const vector<int> arr) {
    int n = arr.size();
    if (n <= 2) { return max(0, max(arr)); }
    int c[n] = {0};
    for (int i=0; i<n; i++) {
        switch (i) {
            case 0: { c[i] = max(0, arr[i]); break; }
            case 1: { c[i] = max(c[i-1], arr[i]); break; }
            default: { c[i] = max(arr[i] + c[i-2], c[i-1]); }
        }

    }
    return c[n-1];
}

// DP, memoises constant number of computations.
//
// Time: O(n)
// Space: O(1)
int max_non_adjacent(const vector<int> arr) {
    int n = arr.size();
    if (n <= 2) { return max(0, max(arr)); }
    int max_exclude_last = max(0, arr[0]);
    int max_include_last = max(max_exclude_last, arr[1]);
    int prev_max = max_include_last;
    for (int i=2; i<n; i++) {
        max_include_last = max(max_include_last, max_exclude_last + arr[i]);
        max_exclude_last = prev_max;
        prev_max = max_include_last;
    }
    return max(max_include_last, max_exclude_last);
}

int main() {
    vector<int> arr = { 2, 4, 6, 2, 5 };
    cout << __max_non_adjacent(arr) << endl;
    cout << _max_non_adjacent(arr) << endl;
    cout << max_non_adjacent(arr) << endl;
}
