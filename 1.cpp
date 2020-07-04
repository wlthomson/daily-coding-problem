#include <iostream>
#include <set>
#include <vector>

using namespace std;

bool two_sum(vector<int> v, int k) {
  set<int> s;
  set<int>::const_iterator it_s;
  vector<int>::const_iterator it_v;
  for (it_v = v.cbegin(); it_v != v.cend(); ++it_v) {
    it_s = s.find(k - *it_v);
    if (it_s != s.cend()) return true;
    s.insert(*it_v);
  }
  return false;
}

int main() {
  vector<int> v = {10, 15, 3, 7};
  int k = 17;
  cout << boolalpha << two_sum(v, k) << endl;
}