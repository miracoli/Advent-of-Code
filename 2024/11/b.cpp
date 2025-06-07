#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <numeric>
#include <cstdint>

using namespace std;

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Error: input.txt not found or inaccessible." << endl;
    return 1;
  }

  unordered_map<uint64_t, uint64_t> stones;
  uint_fast8_t blinks = 75;

  for (int num; inputFile >> num; ++stones[num]);

  unordered_map<uint64_t, uint64_t> next;
  while (blinks--) {
    next.clear();

    for (const auto& [stone, count] : stones) {
      if (stone == 0) {
        next[1] += count;
      } else if (to_string(stone).size() % 2 == 0) {
        string s = to_string(stone);
        int mid = s.size() / 2;
        next[(uint64_t)stoll(s.substr(0, mid))] += count;
        next[(uint64_t)stoll(s.substr(mid))] += count;
      } else {
        next[stone * 2024] += count;
      }
    }

    stones = std::move(next);
  }

  cout << accumulate(stones.begin(), stones.end(), 0LL, [](long long sum, const auto& p) { return sum + p.second; }) << endl;
}
