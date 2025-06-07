#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <queue>
#include <set>
#include <string>
#include <limits>
#include <cstdint>

using namespace std;

constexpr int_fast8_t dx[] = {1, 0, -1, 0};

int main() {
  ifstream input("input.txt");
  vector<string> grid;
  pair<uint_fast16_t, uint_fast16_t> start, end;

  for (string line; getline(input, line); grid.emplace_back(std::move(line))) {
    for (uint_fast8_t col = 0; col < line.size(); ++col) {
      if (line[col] == 'S') {
        start = {grid.size(), col};
      }
    }
  }

  uint_fast32_t rows = grid.size(), cols = grid[0].size();
  vector visited(rows, vector(cols, vector(4, numeric_limits<uint_fast32_t>::max())));
  vector<vector<vector<vector<tuple<int, int, int>>>>> predecessors(rows, vector<vector<vector<tuple<int, int, int>>>>(cols, vector<vector<tuple<int, int, int>>>(4)));

  priority_queue<tuple<uint_fast32_t, uint_fast16_t, uint_fast16_t, uint_fast8_t>, vector<tuple<uint_fast32_t, uint_fast16_t, uint_fast16_t, uint_fast8_t>>, greater<tuple<uint_fast32_t, uint_fast16_t, uint_fast16_t, uint_fast8_t>>> pq;
    
  pq.emplace(0, start.first, start.second, 0);
  visited[start.first][start.second][0] = 0;

  while (!pq.empty()) {
    auto [cost, r, c, dir] = pq.top();
    pq.pop();

    if (grid[r][c] == 'E') {
      end = {r, c};
      break;
    }
    uint_fast16_t nr = r + dx[(dir + 3) & 3], nc = c + dx[dir];
    if (nr >= 0 && nc >= 0 && nr < rows && nc < cols && grid[nr][nc] != '#') {
      if (cost + 1 < visited[nr][nc][dir]) {
        visited[nr][nc][dir] = cost + 1;
        pq.emplace(cost + 1, nr, nc, dir);
        predecessors[nr][nc][dir] = {{r, c, dir}};
      } else if (cost + 1 == visited[nr][nc][dir]) {
        predecessors[nr][nc][dir].emplace_back(r, c, dir);
      }
    }

    for (uint_fast8_t newDir : {(dir + 1) & 3, (dir + 3) & 3}) {
      if (cost + 1000 < visited[r][c][newDir]) {
        visited[r][c][newDir] = cost + 1000;
        pq.emplace(cost + 1000, r, c, newDir);
        predecessors[r][c][newDir] = {{r, c, dir}};
      } else if (cost + 1000 == visited[r][c][newDir]) {
        predecessors[r][c][newDir].emplace_back(r, c, dir);
      }
    }
  }

  set<pair<uint_fast16_t, uint_fast16_t>> unique_tiles;
  queue<tuple<uint_fast16_t, uint_fast16_t, uint_fast8_t>> q;
    
  for (uint_fast8_t dir = 0; dir < 4; dir++) {
    if (visited[end.first][end.second][dir] != numeric_limits<uint_fast32_t>::max()) {
      q.emplace(end.first, end.second, dir);
    }
  }

  while (!q.empty()) {
    auto [row, col, direction] = q.front();
    q.pop();
    unique_tiles.emplace(row, col);

    for (const auto& predecessor : predecessors[row][col][direction]) {
      q.emplace(predecessor);
    }
  }

  cout << unique_tiles.size() << endl;
}
