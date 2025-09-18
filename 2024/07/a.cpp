#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <iterator>

using namespace std;

bool isValid(uint64_t target, const vector<uint64_t>& nums, size_t idx) {
  if (idx == 0) {
    return nums[0] == target;
  }

  uint64_t curr = nums[idx];

  return (target % curr == 0 && isValid(target / curr, nums, idx - 1)) ||
         (target > curr && isValid(target - curr, nums, idx - 1));
}

int main() {
  ifstream in("input.txt");
  uint64_t total = 0;

  for (string line; getline(in, line); ) {
    stringstream ss(line);
    uint64_t target;
    char colon;
    ss >> target >> colon;
    vector<uint64_t> nums{istream_iterator<uint64_t>{ss}, {}};
    total += isValid(target, nums, nums.size() - 1) ? target : 0;
  }

  cout << total << endl;
}
