#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
  std::ifstream inputFile("input.txt");
  if (!inputFile) {
    std::cerr << "Error: Could not open input file.\n";
    return 1;
  }

  std::vector<int> list1;
  std::vector<int> list2;

  int num1;
  int num2;
  while (inputFile >> num1 >> num2) {
    list1.push_back(num1);
    list2.push_back(num2);
  }

  std::ranges::sort(list1);
  std::ranges::sort(list2);

  std::cout << std::inner_product(list1.begin(), list1.end(), list2.begin(), 0, std::plus<>(), [](int a, int b) { return std::abs(a - b); }) << '\n';
}
