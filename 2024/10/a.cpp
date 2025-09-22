#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

int main() {
  ifstream input("input.txt");
  if (!input) {
    cerr << "Error: input.txt not found or inaccessible." << endl;
    return 1;
  }
  queue<pair<int, int>> q;
  vector<vector<char>> grid;
  vector<pair<int,int>> zeroPositions;
  for (string line; getline(input, line) && !line.empty();grid.emplace_back(line.begin(), line.end())) {
    for (int i = 0; i < line.size(); ++i) {
      if(line[i]=='0') {
        zeroPositions.emplace_back(i, grid.size());
      }
    }
  }
  int totalScore = 0, rows = grid.size(), cols = grid[0].size();
  vector<vector<bool>> visited(rows, vector<bool>(cols));
  for(auto [x, y] : zeroPositions) {
    visited.assign(rows, vector<bool>(cols, false));
    q.push({ x, y });
    visited[y][x] = true;
    while (!q.empty()) {
      auto [currentX, currentY] = q.front(); 
      q.pop();
      if (grid[currentY][currentX] == '9') { 
        ++totalScore; 
        continue; 
      }
      for (auto [dx, dy] : { pair<int, int>{0, 1}, pair<int, int>{0, -1}, pair<int, int>{1, 0}, pair<int, int>{-1, 0} }) {
        int neighborX = currentX + dx, neighborY = currentY + dy;
        if (neighborX >= 0 && neighborX < cols && neighborY >= 0 && neighborY < rows && !visited[neighborY][neighborX] && grid[neighborY][neighborX] == grid[currentY][currentX] + 1) {
          visited[neighborY][neighborX] = true;
          q.push({ neighborX, neighborY });
        }
      }
    }
  }
  cout << totalScore << endl;
}
