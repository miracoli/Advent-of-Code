#include <iostream>
#include <fstream>
#include <string>
#include <array>

int main() {
  constexpr int width = 101;
  constexpr int height = 103;

  std::ifstream inputFile("input.txt");

  if (!inputFile) {
    std::cerr << "Error: Could not open input.txt" << std::endl;
    return 1;
  }
  std::array<int, 4> quadrants{};
  int px, py, vx, vy;
  for (std::string line; std::getline(inputFile, line); ) {
    std::sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);

    px = (px + 100 * vx % width + width) % width;
    py = (py + 100 * vy % height + height) % height;
    if (px != width / 2 && py != height / 2) {
      quadrants[(px > width / 2) + 2 * (py > height / 2)]++;
    }
  }

  std::cout << quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3] << std::endl;
}
