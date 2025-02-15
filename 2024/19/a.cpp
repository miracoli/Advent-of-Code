#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string_view>
#include <vector>

std::unordered_map<std::string_view, bool> memo;
std::vector<std::string> patterns, designs;

bool canFormDesign(std::string_view design) {
  if (design.empty()) {
    return true;
  }
  if (memo.count(design)) {
    return memo[design];
  }
  for (const auto &pattern : patterns) {
    if (design.starts_with(pattern) && canFormDesign(design.substr(pattern.size()))) {
      return memo[design] = true;
    }
  }
  return memo[design] = false;
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
  
  int possible = 0;
  for (const auto &designStr : designs) {
    possible += canFormDesign(designStr);
  }
  
  std::cout << possible << std::endl;
}
