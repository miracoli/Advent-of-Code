#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <queue>
#include <iterator>

using namespace std;

constexpr array<array<int, 2>, 4> dirs = {{{1,0}, {0,1}, {-1,0}, {0,-1}}};

int main() {
  ifstream input("input.txt");
  if (!input) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }
  vector<string> map(istream_iterator<string>(input), {});
  int rows = map.size(), cols = map[0].size(), totalCost = 0;
  vector<vector<bool>> globalVisited(rows, vector<bool>(cols, false));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (!globalVisited[i][j]) {
        vector<vector<bool>> localVisited(rows, vector<bool>(cols, false));
        int minX = i, minY = j, maxX = i, maxY = j, area = 1, sides = 0;
        queue<pair<int, int>> q;
        q.emplace(i, j);
        localVisited[i][j] = globalVisited[i][j] = true;

        while (!q.empty()) {
          auto [x, y] = q.front(); 
          q.pop();
          for (const auto& dir : dirs) {
            int nx = x + dir[0], ny = y + dir[1];
            minX = min(minX, nx), maxX = max(maxX, nx);
            minY = min(minY, ny), maxY = max(maxY, ny);
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && map[nx][ny] == map[i][j] && !localVisited[nx][ny]) {
              localVisited[nx][ny] = globalVisited[nx][ny] = true;
              ++area;
              q.emplace(nx, ny);
            }
          }
        }

        for (int x = minX; x < maxX; ++x) {
          for (int y = minY; y < maxY; ++y) {
            bool topLeft = x >= 0 && x < rows && y >= 0 && y < cols && localVisited[x][y] && map[x][y] == map[i][j];
            bool topRight = x >= 0 && x < rows && y+1 >= 0 && y+1 < cols && localVisited[x][y+1] && map[x][y+1] == map[i][j];
            bool bottomLeft = x+1 >= 0 && x+1 < rows && y >= 0 && y < cols && localVisited[x+1][y] && map[x+1][y] == map[i][j];
            bool bottomRight = x+1 >= 0 && x+1 < rows && y+1 >= 0 && y+1 < cols && localVisited[x+1][y+1] && map[x+1][y+1] == map[i][j];
                        
            int windowSum = topLeft + topRight + bottomLeft + bottomRight;
            sides += windowSum % 2;
            if (windowSum == 2) {
              sides += 2 * ((topLeft && bottomRight) || (bottomLeft && topRight));
            }
          }
        }
        totalCost += area * sides;
      }
    }
  }
  cout << totalCost << endl;
}
