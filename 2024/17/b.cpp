#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <ranges>

std::vector<std::int64_t> instructions;
int64_t A, B, C;

std::int64_t comboValue(std::int64_t operand)  {
  return operand < 4 ? operand : operand == 4 ? A : operand == 5 ? B : C;
}

std::int64_t rec(const std::vector<std::int64_t>& program, std::size_t instructionPointer, std::int64_t current = 0) {
  for (std::int64_t i = 0; i < 8; ++i) {
    std::int64_t newCurrent = (current << 3) + i;
    std::vector<std::int64_t> result;
        
    A = newCurrent;
    for (int ip = 0; ip < instructions.size();) {
      std::int64_t opcode = instructions[ip++], operand = instructions[ip++];
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

    if (std::equal(result.begin(), result.end(), program.begin() + instructionPointer)) {
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
  std::ifstream input("input.txt");
  if (!input) {
    std::cerr << "Error: Could not open input file.\n";
    return 1;
  }
  std::string line;
  std::string programOutput;
  std::vector<std::string> contents = std::ranges::istream_view<std::string>(input) | std::ranges::to<std::vector<std::string>>();
 
  instructions = contents[10] | std::views::split(',') | std::views::transform([](auto&& part) { return part[0] - '0'; }) | std::ranges::to<std::vector<int64_t>>();

  std::cout << rec(instructions, instructions.size() - 1) << std::endl;
}
