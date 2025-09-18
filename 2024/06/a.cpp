#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <array>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Error opening file.\n";
    return 1;
  }

  vector<string> map;
  int direction = 0, x = 0, y = 0;
  
  for (string line; getline(inputFile, line); map.push_back(line)) {
    if (auto pos = line.find('^'); pos != string::npos) {
      x = pos, y = map.size();
    }
  }

  set<pair<int, int>> visited{ {x, y} };
  constexpr std::array<int, 4> directionOffsets{0, 1, 0, -1};

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

  cout << visited.size() << endl;
}
