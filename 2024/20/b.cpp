#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <unordered_map>

using namespace std;

constexpr array<array<int, 2>, 4> directions = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
constexpr int maximumCheatDistance = 20;
constexpr int savingsWanted = 100;

int main() {
  ifstream input("input.txt");
  if (!input) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }
  vector<string> grid;
  pair<int, int> pos;
    
  for (string line; getline(input, line); grid.emplace_back(std::move(line))) {
    for (int col = 0; col < line.size(); ++col) {
      if (line[col] == 'S') {
        pos = {grid.size() , col};
      }
    }
  }

  vector<pair<int, int>> path;
  vector<int> locIndex(grid.size() * grid[0].size(), -1);
  int direction = 0;
  int idx = 0;
  auto encode = [&grid](pair<int, int> pos) { return pos.first * grid[0].size() + pos.second; };

  while (grid[pos.first][pos.second] != 'E') {
    path.emplace_back(pos);
    locIndex[ encode(pos) ] = idx++;
        
    for (int d : {direction, (direction + 1) & 3, (direction + 3) & 3}) {
      int nx = pos.first + directions[d][0];
      int ny = pos.second + directions[d][1];
      if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] != '#') {
        pos = {nx, ny};
        direction = d;
        break;
      }
    }
  }
  path.emplace_back(pos); // add end
  locIndex[ encode(pos) ] = idx;

  long long validCheats = 0;
  for (int i = 0; i < (int)path.size(); ++i) {
    auto [x, y] = path[i];
    for (int dx = -maximumCheatDistance; dx <= maximumCheatDistance; ++dx) {
      for (int dy = -maximumCheatDistance; dy <= maximumCheatDistance; ++dy) {
        int D = abs(dx) + abs(dy);
        if (D > maximumCheatDistance) {
          continue;
        }

        int nx = x + dx;
        int ny = y + dy;
        if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size()) {
          continue;
        }

        int key = nx * grid[0].size() + ny;
        if (locIndex[key] >= i + savingsWanted + D) {
          ++validCheats;
        }
      }
    }
  }

  cout << validCheats << endl;
}
