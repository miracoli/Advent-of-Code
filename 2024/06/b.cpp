#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Error opening file.\n";
    return 1;
  }

  vector<string> map;
  int startX = 0, startY = 0;

  for (string line; getline(inputFile, line); map.emplace_back(std::move(line))) {
    if (auto pos = line.find('^'); pos != string::npos) {
      startX = (int)pos; startY = (int)map.size();
    }
  }

  const int H = (int)map.size(), W = (int)map[0].size();
  constexpr int_fast8_t dOff[2][4] = { {-1,0,1,0}, {0,1,0,-1} }; // [dy][dir], [dx][dir]
  auto id = [W](int x, int y){ return y * W + x; };

  vector<bool> seen(W * H, 0);
  vector<tuple<int, int, uint_fast8_t>> candidates;

  int x = startX, y = startY;
  uint_fast8_t direction = 0;
  seen[id(x,y)] = 1;

  while (true) {
    int nx = x + dOff[1][direction], ny = y + dOff[0][direction];
    if (ny < 0 || ny >= H || nx < 0 || nx >= W) {
      break;
    } else if (map[ny][nx] == '#') {
      direction = (direction + 1) & 3;
    } else {
      x = nx; y = ny;
      int cid = id(x,y);
      if (!seen[cid]) {
        seen[cid] = 1;
        candidates.push_back({x, y, direction});
      }
    }
  }

  vector<int> stateStamp(W * H * 4, -1);
  int stamp = 0;
  auto state_key = [&id](int x, int y, int d){ return ((id(x,y) << 2) | d); };

  int endlessLoopCount = 0;

  for (auto cell : candidates) {
    auto px = std::get<0>(cell), py = std::get<1>(cell);
    direction = std::get<2>(cell);

    // Start from predecessor of the obstacle cell
    x = px - dOff[1][direction];
    y = py - dOff[0][direction];

    ++stamp;
    while (true) {
      int nx = x + dOff[1][direction], ny = y + dOff[0][direction];
      if (ny < 0 || ny >= H || nx < 0 || nx >= W) {
         break;
      }
      if ((map[ny][nx] == '#') || (nx == px && ny == py)) { // blocked
        direction = (direction + 1) & 3;
        int key = state_key(x, y, direction);
        if (stateStamp[key] == stamp) {
          ++endlessLoopCount;
          break;
        }
        stateStamp[key] = stamp;
      } else {
        x = nx; y = ny;
      }
    }
  }

  cout << endlessLoopCount << endl;
}
