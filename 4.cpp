#include <iostream>
#include <vector>

using namespace std;

void swap(vector<int> arr, int i, int j) {
  int v = arr[i];
  arr[i] = arr[j];
  arr[j] = v;
}

// Partially order array and return first missing value.
//
// Time: O(n)
// Space: O(1)
int lowest_missing_num(vector<int> nums) {
  if (!(nums.size() > 0)) return 1;
  for (int i = 0; i < nums.size(); i++) {
    while (nums[i] > 0 && nums[i] <= nums.size() && nums[i] != i + 1) {
      int v = nums[i];
      if (nums[i] == nums[v - 1]) break;
      swap(nums, i, v - 1);
    }
  }
  for (int i = 1; i <= nums.size(); i++) {
    int num = nums[i - 1];
    if (num != i) return i;
  }
  return nums.size() + 1;
}

int main() {
  vector<int> nums = {1, 2, 0};
  cout << lowest_missing_num(nums) << endl;
}