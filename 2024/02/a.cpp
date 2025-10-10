#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iterator>
using namespace std;

int main() {
  ifstream file("input.txt");
  if (!file) {
    cerr << "Error: Could not open file 'input.txt'" << endl;
    return 1;
  }

  auto isValid = [](const vector<int>& nums) {
    bool wrongSign = (nums[1] - nums[0]) > 0;
    for (size_t i = 1; i < nums.size(); ++i) {
      int diff = nums[i] - nums[i - 1];
      if (abs(diff) < 1 || abs(diff) > 3 || signbit(diff) == wrongSign) {
        return false;
      }
    }
    return true;
  };

  int validCount = 0;

  for (string line; getline(file, line);) {
    istringstream iss(line);
    vector<int> nums{ istream_iterator<int>(iss), {} };
    if (isValid(nums)) {
      ++validCount;
    }
  }

  cout << validCount << endl;
}
