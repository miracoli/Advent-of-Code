#include <unordered_set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>

using namespace std;

constexpr int N = 71;
constexpr array<int, 4> dx{1, 0, -1, 0};
constexpr array<int, 4> dy{0, 1, 0, -1};

array<array<bool, N>, N> blocked{};
array<array<int, N>, N>  visitStamp{};
int  bfsRun = 1;
array<array<int, N>, N>  parentX{};
array<array<int, N>, N>  parentY{};
unordered_set<int> pathCells;
array<int, N * N> qx{};
array<int, N * N> qy{};

bool bfs() {
  int head = 0;
  int tail = 0;

  qx[tail] = qy[tail++] = 0;
  visitStamp[0][0] = ++bfsRun;
  parentX[0][0] = parentY[0][0] = -1;

  while (head < tail) {
    int x = qx[head];
    int y = qy[head++];
    if (x == N - 1 && y == N - 1) {
      pathCells.clear();
      int cy = y;
      for (int cx = x; cx != -1; ) {
        pathCells.insert(cx * N + cy);
        tie(cx, cy) = make_pair(parentX[cx][cy], parentY[cx][cy]);
      }
      return true;
    }
    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k];
      int ny = y + dy[k];
      if (nx >= 0 && ny >= 0 && nx < N && ny < N && !blocked[nx][ny] && visitStamp[nx][ny] != bfsRun) {
        visitStamp[nx][ny] = bfsRun;
        parentX[nx][ny] = x;
        parentY[nx][ny] = y;
        qx[tail] = nx;
        qy[tail++] = ny;
      }
    }
  }
  pathCells.clear();
  return false;
}

int main() {
  ifstream input("input.txt");
  if (!input) {
    cerr << "Error: unable to open input.txt" << endl;
    return 1;
  }

  bfs();

  int x = 0;
  int y = 0;
  int maxCount = 0;
  bool solvable = true;

  for (string line; getline(input, line) && solvable;) {
    replace(line.begin(), line.end(), ',', ' ');
    (stringstream(line) >> x >> y);

    blocked[x][y] = true;

    if (++maxCount < 1024) {
      continue;
    }

    if (pathCells.contains(x * N + y)) {
      solvable = bfs();
    }
  }

  cout << x << ',' << y << endl;
}
