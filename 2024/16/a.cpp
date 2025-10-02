#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <tuple>
#include <cstdint>
#include <array>

using namespace std;

constexpr array<array<int, 2>, 4> directions{{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};
constexpr std::array<uint_fast8_t, 2> turnOffsets{1, 3};

int main() {
  ifstream input("input.txt");
  if (!input) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }
  vector<string> grid;
  pair<uint_fast16_t, uint_fast16_t> start;

  for (string line; getline(input, line); grid.push_back(std::move(line))) {
    if (auto pos = line.find('S'); pos != string::npos) {
      start = {pos, grid.size()};
    }
  }

  uint_fast16_t rows = grid.size();
  uint_fast16_t cols = grid[0].size();
  vector<uint_fast32_t> visited(rows * cols * 4, numeric_limits<uint_fast32_t>::max());

  priority_queue<tuple<uint_fast32_t, uint_fast16_t, uint_fast16_t, uint_fast8_t>, vector<tuple<uint_fast32_t, uint_fast16_t, uint_fast16_t, uint_fast8_t>>, greater<>> pq;

  pq.emplace(0, start.first, start.second, 0);
  visited[(start.second * cols + start.first) * 4 + 0] = 0;

  while (!pq.empty()) {
    auto [cost, x, y, direction] = pq.top();
    pq.pop();
    if (grid[y][x] == 'E') {
      cout << cost << endl;
      break;
    }

    uint_fast16_t newX = x + directions[direction][0];
    uint_fast16_t newY = y + directions[direction][1];
    if (auto& currentVisited = visited[(newY * cols + newX) * 4 + direction];
        newX < cols && newY < rows && grid[newY][newX] != '#' && cost + 1 < currentVisited) {
      currentVisited = cost + 1;
      pq.emplace(cost + 1, newX, newY, direction);
    }

    for (uint_fast8_t offset : turnOffsets) {
      auto nd = (direction + offset) & 3;
      auto& turnedVisited = visited[(y * cols + x) * 4 + nd];
      if (cost + 1000 < turnedVisited) {
        turnedVisited = cost + 1000;
        pq.emplace(cost + 1000, x, y, nd);
      }
    }
  }
}
