#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <cstdint>
#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
  const int width = 101;
  const int height = 103;
  int seconds = 0, px, py, vx, vy;

  vector<tuple<int, int, int, int>> robots; // (px, py, vx, vy)
  ifstream inputFile("input.txt");

  if (!inputFile) {
    cerr << "Error: Could not open input.txt" << endl;
    return 1;
  }

  for (string line; getline(inputFile, line); robots.emplace_back(px, py, vx, vy)) {
    sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
  }

  vector<uint8_t> map(height * width, false);

  for (++seconds; ; ++seconds) {
    ranges::fill(map, 0);

    bool collision = false;
    for (auto &robot : robots) {
      int x = get<0>(robot) + seconds * get<2>(robot);
      int y = get<1>(robot) + seconds * get<3>(robot);

      x %= width;
      if(x < 0) {
        x += width;
      }
      y %= height;
      if(y < 0) {
        y += height;
      }

      int index = y * width + x;

      if (map[index]) {
        collision = true;
        break;
      }
      map[index] = 1;
    }

    if (!collision) {
      break;
    }
  }

  cout << seconds << endl;
}
