#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string_view>
using namespace std;

unordered_map<string_view, uint64_t> memo;
vector<string> patterns;

uint64_t countWays(string_view design) {
  if (design.empty()) {
    return 1;
  }
  if (auto it = memo.find(design); it != memo.end()) {
    return it->second;
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
  ifstream input("input.txt");
  if (!input) {
    cerr << "Error opening file." << endl;
    return 1;
  }

  vector<string> designs;
  string line;
  getline(input, line);
  stringstream ss(line);
  for (string token; getline(ss, token, ',') >> ws; ) {
    patterns.push_back(std::move(token));
  }

  while (getline(input, line)) {
    if (!line.empty()) {
      designs.push_back(std::move(line));
    }
  }

  uint64_t totalWays = 0;
  for (const auto &design : designs) {
    totalWays += countWays(design);
  }

  cout << totalWays << endl;
}
