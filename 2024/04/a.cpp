#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <array>
using namespace std;

constexpr string TARGET = "XMAS";
constexpr array<array<int, 2>, 8> directions{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}};

int main() {
  ifstream inputFile("input.txt");
  vector<string> grid{istream_iterator<string>{inputFile}, istream_iterator<string>{}};
  int rows = grid.size(), cols = grid[0].size(), count = 0;

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      for (auto [dx, dy] : directions) {
        int x = row, y = col, k = 0;
        for (; k < TARGET.size() && x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == TARGET[k]; ++k) {
          x += dx; y += dy;
        }
        count += (k == TARGET.size());
      }
    }
  }

  cout << count << endl;
}
