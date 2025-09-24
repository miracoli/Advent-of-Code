#include <iostream>
#include <fstream>
#include <string>
#include <array>
using namespace std;

int main() {
  constexpr int width = 101;
  constexpr int height = 103;

  ifstream inputFile("input.txt");

  if (!inputFile) {
    cerr << "Error: Could not open input.txt" << endl;
    return 1;
  }
  array<int, 4> quadrants{};
  int px;
  int py;
  int vx;
  int vy;
  for (string line; getline(inputFile, line); ) {
    sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);

    px = (px + 100 * vx % width + width) % width;
    py = (py + 100 * vy % height + height) % height;
    if (px != width / 2 && py != height / 2) {
      quadrants[(px > width / 2) + 2 * (py > height / 2)]++;
    }
  }

  cout << quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3] << endl;
}
