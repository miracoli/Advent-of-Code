#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iterator>

int main() {
  std::ifstream file("input.txt");
  if (!file) {
    std::cerr << "Error: Could not open file 'input.txt'\n";
    return 1;
  }

  int validCount = 0;

  for (std::string line; std::getline(file, line);) {
    std::istringstream iss(line);
    std::vector<int> nums{std::istream_iterator<int>(iss), {}};
    bool isValidLine = false;
    for (size_t skipIndex = 0; skipIndex < nums.size() && !isValidLine; ++skipIndex) {
      int prev = nums[(skipIndex) ? 0 : 1];
      int next = ((skipIndex <= 1) ? 2 : 1);
      bool wrongSign = !std::signbit(nums[next] - prev);
      bool isValidSkip = true;
      for (size_t i = next; i < nums.size() && isValidSkip; ++i) {
        if (i == skipIndex) {
          continue;
        }
        int diff = nums[i] - prev;
        isValidSkip = !(std::abs(diff) < 1 || std::abs(diff) > 3 || std::signbit(diff) == wrongSign);
        prev = nums[i];
      }
      isValidLine = isValidSkip;
    }
    validCount += isValidLine;
  }

  std::cout << validCount << '\n';
  return 0;
}
