#include <iostream>
#include <unordered_map>

using namespace std;

typedef unsigned int uint;

uint max_distinct_substring(uint k, string s) {
  if (k == 0) return 0;
  uint i = 0, j = 0, c = 0, m = 0;
  unordered_map<char, uint> d;
  unordered_map<uint, char> d_inv;
  for (string::const_iterator it_s = s.cbegin(); it_s != s.cend(); ++it_s) {
    d[*it_s] = j;
    d_inv[j] = *it_s;
    if (d.size() > k) {
      d.erase(d_inv[i]);
      d_inv.erase(i++);
    }
    c = ++j - i;
    if (c > m) m = c;
  }
  return m;
}

int main() {
  uint k = 2;
  string s = "abcba";
  cout << max_distinct_substring(k, s) << endl;
}
