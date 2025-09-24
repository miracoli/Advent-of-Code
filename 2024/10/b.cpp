#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main() {
  ifstream input("input.txt");
  if (!input) {
      cerr << "Error: input.txt not found or inaccessible." << endl;
      return 1;
  }

  vector<vector<char>> grid;
  vector<pair<int, int>> zeroPositions;
  queue<pair<int, int>> q;
  for (string line; getline(input, line) && !line.empty(); grid.emplace_back(line.begin(), line.end())) {
    for (int i = 0; i < line.size(); ++i) {
      if (line[i] == '0') {
        zeroPositions.emplace_back(i, grid.size());
        q.push({i, grid.size()});
      }
    }
  }

  int totalWays = 0;
  int rows = grid.size();
  int cols = grid[0].size();
  vector<vector<int>> ways(rows, vector<int>(cols, 0)); // DP table to store path counts

  for (auto [x, y] : zeroPositions) {
    ways[y][x] = 1; // Each '0' starts with 1 path
  }

  while (!q.empty()) {
    auto [currentX, currentY] = q.front();
    q.pop();

    if (grid[currentY][currentX] == '9') {
        totalWays += ways[currentY][currentX];
        continue;
    }

    for (auto [dx, dy] : { pair<int, int>{0, 1}, pair<int, int>{0, -1}, pair<int, int>{1, 0}, pair<int, int>{-1, 0} }) {
      int neighborX = currentX + dx;
      int neighborY = currentY + dy;
      if (neighborX >= 0 && neighborX < cols && neighborY >= 0 && neighborY < rows && grid[neighborY][neighborX] == grid[currentY][currentX] + 1) {
        if (ways[neighborY][neighborX] == 0) {
          q.push({neighborX, neighborY}); // First visit
        }
        ways[neighborY][neighborX] += ways[currentY][currentX];
      }
    }
  }

  cout << totalWays << endl;
}
