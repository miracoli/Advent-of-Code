#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>

using namespace std;

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }

  uint64_t sum = 0;

  for (string line; getline(inputFile, line);) {
    auto firstIt = ranges::find_if(line, ::isdigit);
    auto lastIt = ranges::find_if(line | views::reverse, ::isdigit);
    if (firstIt != ranges::end(line)) {
      sum += 10 * (*firstIt - '0');
      sum += *lastIt - '0';
    }
  }

  cout << sum << endl;
}
