#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string_view>
#include <vector>
#include <algorithm>
using namespace std;

unordered_map<string_view, bool> memo;
vector<string> patterns;
vector<string> designs;

bool canFormDesign(string_view design) {
  if (design.empty()) return true;
  if (auto it = memo.find(design); it != memo.end()) return it->second;

  for (const auto &pattern : patterns) {
    if (pattern.size() > design.size()) break;
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
    patterns.push_back(std::move(token));
  }

  sort(patterns.begin(), patterns.end(), [](string_view a, string_view b){ return a.size() > b.size(); });

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
