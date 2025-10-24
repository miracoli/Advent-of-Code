#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ranges>
#include <iterator>
#include <cmath>
using namespace std;

bool isValid(const auto& nums, bool wrongSign, int skip = -1) {
  auto filtered = nums | views::filter([&nums, skip](const auto& e) { return skip < 0 || &e != &nums[skip]; });
  auto it = filtered.begin();
  for (auto prev = *it++, index = 1; it != filtered.end(); prev = *it++, ++index) {
    if (auto diff = *it - prev; abs(diff) < 1 || abs(diff) > 3 || signbit(diff) == wrongSign) {
      return skip < 0 && (isValid(nums, wrongSign, index) || isValid(nums, wrongSign, index - 1));
    }
  }
  return true;
}

int main() {
  ifstream file("input.txt");
  if (!file) {
    cerr << "Error: Could not open file 'input.txt'" << endl;
    return 1;
  }

  int validCount = 0;

  for (string line; getline(file, line);) {
    istringstream iss(line);
    vector<int> nums{istream_iterator<int>(iss), {}};
    bool wrongSign = (static_cast<int>(std::signbit(nums[1]-nums[0])) + static_cast<int>(std::signbit(nums[2]-nums[1])) + static_cast<int>(std::signbit(nums[3]-nums[2]))) < 2;
    if (isValid(nums, wrongSign)) {
      ++validCount;
    }
  }

  cout << validCount << endl;
}
