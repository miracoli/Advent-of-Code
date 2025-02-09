#include <iostream>
#include <fstream>
#include <cstdint>

int main() {
  constexpr uint64_t MOD_MASK = (1 << 24) - 1;

  std::ifstream in("input.txt");
  uint64_t secret, sum = 0;

  while (in >> secret) {
    for (uint_fast16_t i = 0; i < 2000; ++i) {
      secret = (secret ^ (secret << 6)) & MOD_MASK;
      secret = (secret ^ (secret >> 5));
      secret = (secret ^ (secret << 11)) & MOD_MASK;
    }
    sum += secret;
  }

  std::cout << sum << std::endl;
}
