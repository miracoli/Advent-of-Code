#include <iostream>
#include <fstream>
#include <vector>
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
    auto firstIt = find_if(line.begin(), line.end(), ::isdigit);
    auto lastIt = find_if(line.rbegin(), line.rend(), ::isdigit);
    if(firstIt != line.end()) {
      sum += 10 * (*firstIt - '0');
      sum += *lastIt - '0';
    }
  }

  cout << sum << endl;
}
