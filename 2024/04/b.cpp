#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  vector<string> grid{istream_iterator<string>(inputFile), {}};
  int count = 0;

  for (int row = 1; row < grid.size() - 1; ++row) {
    for (int col = 1; col < grid[0].size() - 1; ++col) {
      count += grid[row][col] == 'A' &&
               ((grid[row - 1][col - 1] == 'M' && grid[row + 1][col + 1] == 'S' ||
                 grid[row - 1][col - 1] == 'S' && grid[row + 1][col + 1] == 'M') &&
                (grid[row - 1][col + 1] == 'M' && grid[row + 1][col - 1] == 'S' ||
                 grid[row - 1][col + 1] == 'S' && grid[row + 1][col - 1] == 'M'));
    }
  }
  cout << count << endl;
}
