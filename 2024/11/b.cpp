#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
#include <array>
using namespace std;

constexpr array<uint64_t, 20> POW10{
  1ULL, 10ULL, 100ULL, 1000ULL, 10000ULL, 100000ULL, 1000000ULL, 10000000ULL,
  100000000ULL, 1000000000ULL, 10000000000ULL, 100000000000ULL,
  1000000000000ULL, 10000000000000ULL, 100000000000000ULL, 1000000000000000ULL,
  10000000000000000ULL, 100000000000000000ULL, 1000000000000000000ULL,
  10000000000000000000ULL
};

struct Node { uint64_t stone, count; };

void sort_and_merge(vector<Node>& v) {
  ranges::sort(v, [](const Node& a, const Node& b) {
    return a.stone < b.stone;
  });
  size_t w = 0;
  for (size_t i = 0; i < v.size(); ) {
    const uint64_t stone = v[i].stone;
    uint64_t total = 0;
    do {
      total += v[i].count; ++i;
    } while (i < v.size() && v[i].stone == stone);
    v[w++] = {stone, total};
  }
  v.resize(w);
}

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Error: input.txt not found or inaccessible." << endl;
    return 1;
  }

  vector<Node> stones, next;
  for (uint64_t num; inputFile >> num; stones.emplace_back(num, 1)); // Read input stones as (stone,1),

  uint_fast8_t blinks = 75;
  while (blinks--) {
    next.clear();

    for (const auto& [stone, count] : stones) {
      if (stone == 0) {
        next.emplace_back(1ULL, count);
      } else {
        uint_fast8_t d = 1;
        for (; stone >= POW10[d]; ++d);
        if ((d & 1) == 0) {
          const uint64_t div = POW10[d / 2];
          const uint64_t left  = stone / div;
          const uint64_t right = stone % div;
          next.emplace_back(left,  count);
          next.emplace_back(right, count);
        } else {
          next.emplace_back(stone * 2024ULL, count);
        }
      }
    }
    sort_and_merge(next); // Sort by stone and merge counts of equal stones.
    stones.swap(next);
  }

  cout << accumulate(stones.begin(), stones.end(), 0ULL, [](uint64_t sum, const auto& e) { return sum + e.count; }) << endl;
}
