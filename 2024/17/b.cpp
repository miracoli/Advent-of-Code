#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <ranges>
using namespace std;

vector<int64_t> instructions;
int64_t A;
int64_t B;
int64_t C;

int64_t comboValue(int64_t operand)  {
  return operand < 4 ? operand : operand == 4 ? A : operand == 5 ? B : C;
}

int64_t rec(const vector<int64_t>& program, size_t instructionPointer, int64_t current = 0) {
  for (int64_t i = 0; i < 8; ++i) {
    int64_t newCurrent = (current << 3) + i;
    vector<int64_t> result;
        
    A = newCurrent;
    for (int ip = 0; ip < instructions.size();) {
      int64_t opcode = instructions[ip];
      ++ip;
      int64_t operand = instructions[ip];
      ++ip;
      switch (opcode) {
        case 0:  // adv
            A /= (1 << comboValue(operand));
            break;
        case 1: // bxl
            B ^= operand;
            break;
        case 2: // bst
            B = comboValue(operand) & 7;
            break;
        case 3: // jnz
            if (A) {
              ip = operand;
            }
            break;
        case 4: // bxc
            B ^= C;
            break;
        case 5: // out
            result.push_back(comboValue(operand) & 7);
            break;
        case 6: // bdv
            B = A / (1 << comboValue(operand));
            break;
        default: // cdv
            C = A / (1 << comboValue(operand));
            break;
      }
    }

    if (equal(result.begin(), result.end(), program.begin() + instructionPointer)) {
      if (instructionPointer == 0) {
        return newCurrent;
      }
      auto result = rec(program, instructionPointer - 1, newCurrent);
      if (result != -1) {
        return result;
      }
    }
  }
  return -1;
}

int main() {
  ifstream input("input.txt");
  if (!input) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }
  string line;
  string programOutput;
  vector<string> contents = ranges::istream_view<string>(input) | ranges::to<vector<string>>();
 
  instructions = contents[10] | views::split(',') | views::transform([](auto&& part) { return part[0] - '0'; }) | ranges::to<vector<int64_t>>();

  cout << rec(instructions, instructions.size() - 1) << endl;
}
