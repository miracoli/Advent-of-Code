#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string_view>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <functional>
using namespace std;

unordered_map<string_view, bool> memo;
array<vector<string>, 256> buckets;

bool canFormDesign(string_view design) {
  if (design.empty()) return true;
  if (auto it = memo.find(design); it != memo.end()) return it->second;

  const auto& cand = buckets[design[0]];

  for (const auto &pattern : cand) {
    if (design.starts_with(pattern) && canFormDesign(design.substr(pattern.size()))) {
      return memo[design] = true;
    }
  }
  return memo[design] = false;
}

int main() {
  ifstream input("input.txt");
  if (!input) {
    cerr << "Error opening file." << endl;
    return 1;
  }

  string line;
  getline(input, line);
  stringstream ss(line);
  for (string token; getline(ss, token, ',') >> ws; ) {
    if (!token.empty()) {
      buckets[token[0]].push_back(std::move(token));
    }
  }

  vector<string> designs;
  while (getline(input, line)) {
    if (!line.empty()) {
      designs.push_back(std::move(line));
    }
  }

  int possible = 0;
  for (const auto &designStr : designs) {
    if (canFormDesign(designStr)) {
      ++possible;
    }
  }

  cout << possible << endl;
}
