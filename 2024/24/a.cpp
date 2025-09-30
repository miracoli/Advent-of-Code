#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <tuple>
#include <cstdint>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Error: Could not open input file." << endl;
    return 1;
  }

  unordered_map<string, bool> wireValues;
  queue<tuple<string, string, string, string>> pendingGates;

  for (string line; getline(inputFile, line) && !line.empty(); wireValues[line.substr(0, 3)] = line[5] - '0');

  for (string in1, in2, op, out, _; inputFile >> in1 >> op >> in2 >> _ >> out; pendingGates.emplace(in1, in2, op, out));

  while (!pendingGates.empty()) {
    auto [input1, input2, op, output] = pendingGates.front();
    pendingGates.pop();

    if (wireValues.contains(input1) && wireValues.contains(input2)) {
      bool v1 = wireValues[input1];
      bool v2 = wireValues[input2];
      if (op == "AND") {
        wireValues[output] = v1 & v2;
      } else if (op == "OR") {
        wireValues[output] = v1 | v2;
      } else {
        wireValues[output] = v1 ^ v2;
      }
    } else {
      pendingGates.emplace(input1, input2, op, output);
    }
  }

  uint64_t binaryResult = 0;
  for (const auto& [wire, value] : wireValues) {
    if (wire[0] == 'z') {
      binaryResult |= (uint64_t(value) << stoi(&wire[1]));
    }
  }

  cout << binaryResult << endl;
}
