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
    enable = (*it).str() == "do()" ? true : (*it).str() == "don't()" ? false : enable;
    sum += enable && (*it)[1].matched ? stoi((*it)[1]) * stoi((*it)[2]) : 0;
  }

  cout << sum;
}