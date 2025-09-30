#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <iterator>
#include <cstdint>
using namespace std;

int main() {
  ifstream file("input.txt");
  if (!file) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }
  string content((istreambuf_iterator<char>(file)), {});
  const regex r(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))");
  uint64_t sum = 0;
  bool enable = true;

  for (sregex_iterator it(content.begin(), content.end(), r), end; it != end; ++it) {
    const string command = (*it).str();
    if (command == "do()") {
      enable = true;
    } else if (command == "don't()") {
      enable = false;
    }
    sum += enable && (*it)[1].matched ? stoi((*it)[1]) * stoi((*it)[2]) : 0;
  }

  cout << sum;
}
