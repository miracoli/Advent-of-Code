#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <iterator>
#include <cstdint>

int main() {
  std::ifstream file("input.txt");
  if (!file) {
    std::cerr << "Error: Could not open input file.\n";
    return 1;
  }
  std::string content((std::istreambuf_iterator<char>(file)), {});
  const std::regex r(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))");
  uint64_t sum = 0;
  bool enable = true;

  for (std::sregex_iterator it(content.begin(), content.end(), r), end; it != end; ++it) {
    enable = (*it).str() == "do()" ? true : (*it).str() == "don't()" ? false : enable;
    sum += enable && (*it)[1].matched ? std::stoi((*it)[1]) * std::stoi((*it)[2]) : 0;
  }

  std::cout << sum;
}