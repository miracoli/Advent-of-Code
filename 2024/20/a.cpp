#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>

using namespace std;

constexpr array<array<int, 2>, 4> directions = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
constexpr int maximumCheatDistance = 2;
constexpr int savingsWanted = 100;

int main() {
  ifstream input("input.txt");
  vector<string> grid;
  pair<int, int> pos;
    
  for (string line; getline(input, line); grid.emplace_back(move(line))) {
    for (int col = 0; col < line.size(); ++col) {
      if (line[col] == 'S') {
        pos = {grid.size() , col};
      }
    }
  }
    
  vector<pair<int, int>> path;
  int direction = 0;
    
  while (grid[pos.first][pos.second] != 'E') {
    path.push_back(pos);
        
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
  path.push_back(pos); // add end
    
  int validCheats = 0;
  for (auto i = 0; i < path.size(); ++i) {
    for (auto j = path.size() - 1; j > i + 1; --j) {
      if (j - i < savingsWanted) {
        break;
      }
      int cheatDistance = abs(path[i].first - path[j].first) + abs(path[i].second - path[j].second);
      int cheatSavings = (j - i) - cheatDistance;
      if (cheatDistance <= maximumCheatDistance && cheatSavings >= savingsWanted) {
        ++validCheats;
      }
    }
  }
  
  cout << validCheats << endl;
}
