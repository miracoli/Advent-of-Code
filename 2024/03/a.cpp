#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <iterator>
#include <cstdint>
using namespace std;

int main() {
  ifstream file("input.txt");
  string content((istreambuf_iterator<char>(file)), {});
  const regex r(R"(mul\((\d{1,3}),(\d{1,3})\))");
  uint64_t sum = 0;
  for (sregex_iterator it(content.begin(), content.end(), r), end; it != end; ++it) {
    sum += stoi((*it)[1]) * stoi((*it)[2]);
  }
  cout << sum;
}
