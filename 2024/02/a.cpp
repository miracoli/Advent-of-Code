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

  int validCount = 0;

  for (string line; getline(file, line);) {
    istringstream iss(line);
    vector<int> nums{ istream_iterator<int>(iss), {} };
    bool wrongSign = !signbit(nums[1] - nums[0]);
    bool isValid = true;
    for (size_t i = 1; i < nums.size() && isValid; ++i) {
      int diff = nums[i] - nums[i - 1];
      isValid = !(abs(diff) < 1 || abs(diff) > 3 || signbit(diff) == wrongSign);
    }
    validCount += (int) isValid;
  }

  cout << validCount << endl;
}
