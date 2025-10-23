#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
using namespace std;

int main() {
  ifstream file("input.txt");
  if (!file) {
    cerr << "Error opening file: input.txt" << endl;
    return 1;
  }

  vector<uint32_t> locks;
  vector<uint32_t> keys;
  auto parseKeyOrLock = [&file, &locks, &keys]() {
    uint32_t packed = 0;
    string line;
    for (size_t row = 0; row < 6 && getline(file, line); ++row) {
      for (size_t col = 0; col < 5; ++col) {
        if (line[col] == '#') {
          packed |= (1U << (row * 5 + col));
        }
      }
    }
    (packed & (1U << 29) ? locks : keys).push_back(packed);
  };
  for (string line; getline(file, line);) {
    if (!line.empty()) {
      parseKeyOrLock();
    }
  }

  auto isValidPair = [](const auto& tup) {
    auto [lock, key] = tup;
    return (lock & key) == 0;
  };

  cout << static_cast<uint64_t>(ranges::count_if(views::cartesian_product(locks, keys), isValidPair))
       << endl;
}
