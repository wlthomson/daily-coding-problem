#include <functional>
#include <iostream>
#include <set>
#include <unordered_map>

using namespace std;

typedef pair<char, int> char_count;
typedef function<bool(pair<char, int>, pair<char, int>)> comparator;

bool freq_compare(pair<char, int> a, pair<char, int> b) {
  return a.second > b.second;
}

// Build map of character frequencies and sort by value.
//
// Time: O(n log n)
// Space: O(n)
void freq_sort(string str) {
  unordered_map<char, int> d;
  unordered_map<char, int>::iterator it_d;
  for (string::const_iterator cit_str = str.cbegin(); cit_str != str.cend();
       ++cit_str) {
    it_d = d.find(*cit_str);
    if (it_d == d.end()) {
      d[*cit_str] = 1;
    } else {
      ++(it_d->second);
    }
  }
  multiset<char_count, comparator> freq_set(d.cbegin(), d.cend(), freq_compare);
  for (multiset<char_count>::const_iterator cit_set = freq_set.cbegin();
       cit_set != freq_set.cend(); ++cit_set) {
    cout << string(cit_set->second, cit_set->first);
  }
  cout << endl;
}

int main() { freq_sort("tweet"); }