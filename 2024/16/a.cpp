#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <tuple>
#include <cstdint>

using namespace std;

constexpr int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main() {
  ifstream input("input.txt");
  vector<string> grid;
  pair<uint_fast16_t, uint_fast16_t> start;

  for (string line; getline(input, line); grid.emplace_back(move(line))) {
    if (auto pos = line.find('S'); pos != string::npos) {
      start = {pos, grid.size()};
    }
  }

  uint_fast16_t rows = grid.size(), cols = grid[0].size();
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

    uint_fast16_t newX = x + directions[direction][0], newY = y + directions[direction][1];
    auto& currentVisited = visited[(newY * cols + newX) * 4 + direction];
    if (newX < cols && newY < rows && grid[newY][newX] != '#' && cost + 1 < currentVisited) {
      currentVisited = cost + 1;
      pq.emplace(cost + 1, newX, newY, direction);
    }

    for (uint_fast8_t nd : {(direction + 1) & 3, (direction + 3) & 3}) {
      auto& turnedVisited = visited[(y * cols + x) * 4 + nd];
      if (cost + 1000 < turnedVisited) {
        turnedVisited = cost + 1000;
        pq.emplace(cost + 1000, x, y, nd);
      }
    }
  }
}
