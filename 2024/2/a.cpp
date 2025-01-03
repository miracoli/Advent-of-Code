#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

int main() {
  std::ifstream file("input.txt");
  if (!file) {
    std::cerr << "Error: Could not open file 'input.txt'\n";
    return 1;
  }

  int validCount = 0;

  for (std::string line; std::getline(file, line);) {
    std::istringstream iss(line);
    std::vector<int> nums{ std::istream_iterator<int>(iss), {} };
    bool wrongSign = !std::signbit(nums[1] - nums[0]);
    bool isValid = true;
    for (size_t i = 1; i < nums.size() && isValid; ++i) {
      int diff = nums[i] - nums[i - 1];
      isValid = !(std::abs(diff) < 1 || std::abs(diff) > 3 || std::signbit(diff) == wrongSign);
    }
    validCount += (int) isValid;
  }

  std::cout << validCount << std::endl;
  return 0;
}