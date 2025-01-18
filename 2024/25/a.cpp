#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

int main() {
  std::ifstream file("input.txt");
  if (!file) {
    std::cerr << "Error opening file: input.txt" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::vector<uint32_t> locks, keys;
  for (std::string line; std::getline(file, line);) {
    if (!line.empty()) {
      uint32_t packed = 0;
      for (size_t row = 0; row < 6 && std::getline(file, line); ++row) {
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

  std::cout << validPairs << std::endl;
}
