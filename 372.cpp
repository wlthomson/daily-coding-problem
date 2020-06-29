#include <cmath>
#include <iostream>

using namespace std;

typedef unsigned int uint;

uint digits(uint n) {
  if (n == 0) return 1;
  return (uint)floor(log10(n)) + 1;
}

int main() {
  uint n;
  cin >> n;
  cout << digits(n) << endl;
}