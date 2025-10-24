#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <array>
#include <string>
#include <cstdint>
#include <ranges>

using namespace std;

const unordered_map<char, array<int8_t, 2>> positions = {{'7', {0, 0}}, {'8', {0, 1}}, {'9', {0, 2}},
                                                   {'4', {1, 0}}, {'5', {1, 1}}, {'6', {1, 2}},
                                                   {'1', {2, 0}}, {'2', {2, 1}}, {'3', {2, 2}},
                                                   {'0', {3, 1}}, {'A', {3, 2}}, {'^', {0, 1}},
                                                   {'a', {0, 2}}, {'<', {1, 0}}, {'v', {1, 1}}, {'>', {1, 2}}};
const unordered_map<char, array<int8_t, 2>> directions = {{'^', {-1, 0}}, {'v', {1, 0}}, {'<', {0, -1}}, {'>', {0, 1}}};
unordered_map<string, uint64_t> cache;
constexpr uint_fast8_t limit = 25;

uint64_t solve(const string& path, char depth = 0) {
  auto key = path + depth;
  uint64_t& result = cache[key];
  if (result) {
    return result;
  }

  auto curr = positions.at(depth ? 'a' : 'A');
  auto avoid = depth ? array<int8_t, 2>{0, 0} : array<int8_t, 2>{3, 0};
  result = 0;

  for (char c : path) {
    auto next = positions.at(c);
        
    string movePath = string(abs(next[0] - curr[0]), (next[0] < curr[0] ? '^' : 'v')) + string(abs(next[1] - curr[1]), (next[1] < curr[1] ? '<' : '>'));
    ranges::sort(movePath);

    uint64_t minLen = UINT64_MAX;
    do {
      auto temp = curr;
      if (ranges::all_of(movePath, [&temp, &avoid](char step) { temp[0] += directions.at(step)[0], temp[1] += directions.at(step)[1]; return temp != avoid; })) {
        minLen = min(minLen, (depth == limit ? movePath.size() + 1 : solve(movePath + 'a', depth + 1)));
      }
    } while (ranges::next_permutation(movePath).found);

    result += minLen;
    curr = next;
  }
  return result;
}

int main() {
  ifstream fin("input.txt");
  if (!fin) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }
  vector<pair<string, int>> input;
  for (string line; getline(fin, line); input.emplace_back(std::move(line), stoi(line)));

  cout << transform_reduce(input.begin(), input.end(), 0ULL, plus<>(), [](const auto& p) { return solve(p.first) * p.second; }) << endl;
}
