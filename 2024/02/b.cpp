#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ranges>
#include <iterator>
#include <cmath>

bool isValid(auto&& nums, bool wrongSign, int skip = -1) {
  auto filtered = nums | std::views::filter([&nums, skip](auto& e) { return skip < 0 || &e != &nums[skip]; });
  auto it = filtered.begin();
  for (auto prev = *it++, index = 1; it != filtered.end(); prev = *it++, ++index) {
    if (auto diff = *it - prev; std::abs(diff) < 1 || std::abs(diff) > 3 || std::signbit(diff) == wrongSign) {
      return skip < 0 && (isValid(nums, wrongSign, index) || isValid(nums, wrongSign, index - 1));
    }
  }
  return true;
}

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
    bool wrongSign = (std::signbit(nums[1] - nums[0]) + std::signbit(nums[2] - nums[1]) + std::signbit(nums[3] - nums[2])) < 2;
    validCount += isValid(nums, wrongSign);
  }

  std::cout << validCount << '\n';
}
