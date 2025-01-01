#include <iostream>
#include <fstream>
#include <regex>

int main() {
  std::ifstream file("input.txt");
  std::string content((std::istreambuf_iterator<char>(file)), {});
  const std::regex r(R"(mul\((\d{1,3}),(\d{1,3})\))");
  uint64_t sum = 0;
  for (std::sregex_iterator it(content.begin(), content.end(), r), end; it != end; ++it) {
    sum += std::stoi((*it)[1]) * std::stoi((*it)[2]);
  }
  std::cout << sum;
}
