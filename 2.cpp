#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<int>& v) {
  size_t n = v.size();
  for (size_t i = 0; i < n; ++i) {
    if (i == 0) out << "[";
    out << v[i];
    if (i != n - 1)
      out << ", ";
    else
      out << "]";
  }
  return out;
}

// Trivial solution using division.
//
// Time: O(n)
// Space: O(n)
vector<int> products_div(vector<int> v) {
  int product = accumulate(v.cbegin(), v.cend(), 1, multiplies<int>());

  vector<int> u;
  for (vector<int>::const_iterator cit = v.cbegin(); cit != v.cend(); ++cit) {
    u.push_back(product / *cit);
  }
  return u;
}

// Dynamic programming solution without division.
//
// Time: O(n)
// Space: O(n)
vector<int> products_dyn(vector<int> v) {
  vector<int> prefix_products;
  vector<int> suffix_products;
  for (vector<int>::const_iterator cit = v.cbegin(); cit != v.cend(); ++cit) {
    int prefix_product = accumulate(v.cbegin(), cit, 1, multiplies<int>());
    int suffix_product = accumulate(cit + 1, v.cend(), 1, multiplies<int>());
    prefix_products.push_back(prefix_product);
    suffix_products.push_back(suffix_product);
  }
  
  vector<int> u;
  for (int i = 0; i < v.size(); ++i) {
    u.push_back(prefix_products[i] * suffix_products[i]);
  }

  return u;
}

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  cout << products_div(v) << endl;
  cout << products_dyn(v) << endl;
}