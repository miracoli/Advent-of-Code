#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <array>
#include <iterator>

using namespace std;

constexpr array<array<int, 2>, 4> dirs = {{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};

int main() {
  ifstream input("input.txt");
  if (!input) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }
  vector<string> grid(istream_iterator<string>(input), {});
  vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
  int total = 0;

  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].size(); ++j) {
      if (!visited[i][j]) {
        queue<pair<int, int>> q;
        q.emplace(i, j);
        visited[i][j] = true;
        int area = 1;
        int perimeter = 0;

        while (!q.empty()) {
          auto [cx, cy] = q.front();
          q.pop();
          for (const auto& dir : dirs) {
            int nx = cx + dir[0];
            int ny = cy + dir[1];
            if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size() || grid[nx][ny] != grid[i][j]) {
              ++perimeter;
            } else if (!visited[nx][ny]) {
              visited[nx][ny] = true;
              ++area;
              q.emplace(nx, ny);
            }
          }
        }
        total += area * perimeter;
      }
    }
  }

  cout << total << endl;
}
