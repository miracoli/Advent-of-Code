#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iterator>
#include <algorithm>
#include <array>
using namespace std;

constexpr uint_fast32_t MOD_MASK = (1ULL << 24) - 1;
constexpr size_t STATE_SPACE_SIZE = 19 * 19 * 19 * 19;

int main() {
  ifstream inputFile("input.txt");
  vector<uint_fast32_t> buyerSecrets((istream_iterator<uint_fast32_t>(inputFile)), istream_iterator<uint_fast32_t>());
  array<int_fast16_t, STATE_SPACE_SIZE> sequenceContributions = {0};
  array<uint_fast16_t, STATE_SPACE_SIZE> sequenceLastBuyer = {0};
  int_fast16_t maxContributedValue = 0;
  uint_fast16_t currentBuyerId = 0;
  array<int_fast8_t, 2001> priceHistory = {0};

  for (uint_fast32_t secret : buyerSecrets) {
    ++currentBuyerId;

    for (uint_fast16_t iteration = 0; iteration < 2001; ++iteration) {
      int_fast8_t currentPrice = secret % 10;
      priceHistory[iteration] = currentPrice;
      secret ^= (secret << 6) & MOD_MASK;
      secret ^= (secret >> 5);
      secret ^= (secret << 11) & MOD_MASK;

      if (iteration >= 4) {
        int_fast32_t delta1 = priceHistory[iteration - 4] - priceHistory[iteration - 3];
        int_fast32_t delta2 = priceHistory[iteration - 3] - priceHistory[iteration - 2];
        int_fast32_t delta3 = priceHistory[iteration - 2] - priceHistory[iteration - 1];
        int_fast32_t delta4 = priceHistory[iteration - 1] - currentPrice;
        uint_fast32_t stateIndex = (((delta1 + 9) * 19 + (delta2 + 9)) * 19 + (delta3 + 9)) * 19 + (delta4 + 9);

        if (sequenceLastBuyer[stateIndex] != currentBuyerId) {
           sequenceLastBuyer[stateIndex] = currentBuyerId;
           sequenceContributions[stateIndex] += currentPrice;
           maxContributedValue = max(maxContributedValue, sequenceContributions[stateIndex]);
        }
      }
    }
  }

  cout << maxContributedValue << endl;
}
