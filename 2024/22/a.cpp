#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream in("input.txt");
  if (!in) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }
  uint_fast64_t sum = 0;
  uint_fast32_t secret;

  const auto jump_2000 = [](uint_fast32_t n) {
    uint_fast32_t acc  = 0;
    uint_fast32_t mask = 0x00F33FA2u; // see README.MD how this is computed
    for (uint_fast8_t b = 0; b < 24; ++b) {
      if (mask & 1u) {
        acc ^= n;
      }

      n ^= (n << 6)  & ((1u << 24) - 1u);
      n ^=  (n >> 5);
      n ^= (n << 11) & ((1u << 24) - 1u);
      n &=  ((1u << 24) - 1u);

      mask >>= 1u;
    }
    return acc;
  };

  while (in >> secret) {
    sum += jump_2000(secret);
  }

  cout << sum << endl;
}
