#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;
constexpr int RED_CUBES = 12;
constexpr int GREEN_CUBES = 13;
constexpr int BLUE_CUBES = 14;
const regex pair_re(R"((\d+)\s*(red|green|blue))");

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }

  uint64_t sumGameIdPossible = 0;

  for (string line; getline(inputFile, line);) {
    const auto end = sregex_iterator();
    int maxRed = 0;
    int maxBlue = 0;
    int maxGreen = 0;

    for (auto it = sregex_iterator(line.begin(), line.end(), pair_re); it != end; ++it) {
      const int count = stoi((*it)[1]);
      const string color = (*it)[2];

      if (color == "red")   {
        maxRed = max(maxRed,   count);
      } else if (color == "green") {
        maxGreen = max(maxGreen, count);
      } else if (color == "blue") {
        maxBlue = max(maxBlue,  count);
      } 
    }
    sumGameIdPossible += maxRed * maxBlue * maxGreen;
  }

  cout << sumGameIdPossible << endl;
}
