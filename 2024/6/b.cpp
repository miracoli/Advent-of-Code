#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) return cerr << "Error opening file.\n", 1;

  vector<string> map;
  int startX = 0, startY = 0;

  for (string line; getline(inputFile, line); map.push_back(line)) {
    if (auto pos = line.find('^'); pos != string::npos) {
      startX = pos, startY = map.size();
    }
  }

  constexpr int directionOffsets[] = { 0, 1, 0, -1 };
  int x = startX, y = startY, direction = 0, endlessLoopCount = 0;
  set<pair<int, int>> visited{ {x, y} };
  while (true) {
    int nx = x + directionOffsets[direction], ny = y + directionOffsets[(direction + 3) & 3];
    if (ny < 0 || ny >= map.size() || nx < 0 || nx >= map[0].size()) {
      break;
    } else if (map[ny][nx] == '#') {
      direction = (direction + 1) & 3;
    } else {
      visited.insert({ x = nx, y = ny });
    }
  }

  for (auto [px, py] : visited) {
    map[py][px] = '#'; // Place obstacle

    set<tuple<int, int, int>> states; // Track position and direction
    x = startX, y = startY, direction = 0;

    while (true) {
      int nx = x + directionOffsets[direction], ny = y + directionOffsets[(direction + 3) & 3];
      if (ny < 0 || ny >= map.size() || nx < 0 || nx >= map[0].size()) { 
        break;
      } else if (map[ny][nx] == '#') {
        direction = (direction + 1) & 3; // Turn right
        if (!states.insert({ x, y, direction }).second) {
          ++endlessLoopCount; // Endless loop detected
          break;
        }
      } else {
        x = nx, y = ny;
      }
    }
    map[py][px] = '.'; // Remove obstacle
  }

  cout << "Number of visited positions causing endless loops: " << endlessLoopCount << endl;
  return 0;
}
