#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string_view>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

unordered_map<string, bool> memo;
vector<string> patterns;

bool canFormDesign(string_view design) {
  if (design.empty()) {
    return true;
  }

  string key(design);
  auto [it, inserted] = memo.try_emplace(key, false);
  if (!inserted) return it->second;

  bool can_form = false;
  for (const auto &pattern : patterns) {
    if (pattern.size() > design.size()) continue;
    if (design.starts_with(pattern) && canFormDesign(design.substr(pattern.size()))) {
      can_form = true;
      break;
    }
  }

  memo[key] = can_form;
  return can_form;
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

  sort(patterns.begin(), patterns.end(),
       [](const string &a, const string &b) { return a.size() > b.size(); });

  int possible = 0;
  while (getline(input, line)) {
    if (!line.empty() && canFormDesign(line)) {
      ++possible;
    }
  }

  cout << possible << endl;
}
