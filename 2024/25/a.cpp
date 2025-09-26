#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
using namespace std;

int main() {
  ifstream file("input.txt");
  if (!file) {
    cerr << "Error opening file: input.txt" << endl;
    exit(EXIT_FAILURE);
  }

  vector<uint32_t> locks;
  vector<uint32_t> keys;
  for (string line; getline(file, line);) {
    if (!line.empty()) {
      uint32_t packed = 0;
      for (size_t row = 0; row < 6 && getline(file, line); ++row) {
        for (size_t col = 0; col < 5; ++col) {
          if (line[col] == '#') {
            packed |= (1U << (row * 5 + col));
          }
        }
      }
      (packed & (1 << 29) ? locks : keys).push_back(packed);
    }
  }

  int validPairs = 0;
  for (auto lock : locks) {
    for (auto key : keys) {
      validPairs += !(lock & key);
    }
  }

  cout << validPairs << endl;
}
