#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ranges>

using namespace std;

int comboValue(int operand, int A, int B, int C) { 
  return operand < 4 ? operand : operand == 4 ? A : operand == 5 ? B : C;
}

int main() {
  ifstream input("input.txt");
  bool first = true;
  std::vector<std::string> contents = std::ranges::istream_view<std::string>(input) | std::ranges::to<std::vector<std::string>>();
  int64_t A = stoi(contents[2]), B = stoi(contents[5]), C = stoi(contents[8]);
  std::vector<int> program= contents[10] | std::views::split(',') | std::views::transform([](auto&& part) { return part[0] - '0'; }) | std::ranges::to<std::vector<int>>();

  for (int instructionPointer = 0; instructionPointer < program.size();) {
    int opcode = program[instructionPointer++], operand = program[instructionPointer++];

    switch (opcode) {
      case 0:  // adv
        A /= 1 << comboValue(operand, A, B, C); 
        break;
      case 1:  // bxl
        B ^= operand; 
        break; 
      case 2:  // bst
        B = comboValue(operand, A, B, C) & 7; 
        break; 
      case 3:  // jnz
        if (A) {
          instructionPointer = operand;
        }
        break; 
      case 4:  // bxc
        B ^= C; 
        break; 
      case 5:  // out
        cout << (first ? "" : ",") << (comboValue(operand, A, B, C) & 7);
        first = false;
        break; 
      case 6:  // bdv
        B = A / (1 << comboValue(operand, A, B, C)); 
        break; 
      default:  // cdv
        C = A / (1 << comboValue(operand, A, B, C)); 
        break; 
    }
  }
}