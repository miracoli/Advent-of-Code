#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <cstdint>
#include <cstdio>
#include <algorithm>

int main() {
  const int width = 101;
  const int height = 103;
  int seconds = 0, px, py, vx, vy;

  std::vector<std::tuple<int, int, int, int>> robots; // (px, py, vx, vy)
  std::ifstream inputFile("input.txt");

  if (!inputFile) {
    std::cerr << "Error: Could not open input.txt" << std::endl;
    return 1;
  }

  for (std::string line; std::getline(inputFile, line); robots.emplace_back(px, py, vx, vy)) {
    std::sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
  }

  std::vector<uint8_t> map(height * width, false);

  for (++seconds; ; ++seconds) {
    std::ranges::fill(map, 0);

    bool collision = false;
    for (auto &robot : robots) {
      int x = std::get<0>(robot) + seconds * std::get<2>(robot);
      int y = std::get<1>(robot) + seconds * std::get<3>(robot);

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

  std::cout << seconds << std::endl;
}
