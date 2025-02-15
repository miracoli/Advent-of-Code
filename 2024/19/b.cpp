#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string_view>

std::unordered_map<std::string_view, uint64_t> memo;
std::vector<std::string> patterns, designs;

uint64_t countWays(std::string_view design) {
  if (design.empty()) {
    return 1;
  }
  if (memo.count(design)) {
    return memo[design];
  }

  uint64_t ways = 0;
  for (const auto &pattern : patterns) {
    if (design.starts_with(pattern)) {
      ways += countWays(design.substr(pattern.size()));
    }
  }
  return memo[design] = ways;
}

int main() {
  std::ifstream input("input.txt");
  if (!input) {
    std::cerr << "Error opening file.\n";
    return 1;
  }

  std::string line;
  std::getline(input, line);
  std::stringstream ss(line);
  for (std::string token; std::getline(ss, token, ',') >> std::ws; ) {
    patterns.emplace_back(std::move(token));
  }

  while (std::getline(input, line)) {
    if (!line.empty()) {
      designs.emplace_back(std::move(line));
    }
  }

  uint64_t totalWays = 0;
  for (const auto &design : designs) {
    totalWays += countWays(design);
  }

  std::cout << totalWays << std::endl;
}
