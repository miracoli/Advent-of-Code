#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
  std::ifstream inputFile("input.txt");
  if (!inputFile) return std::cerr << "Error: Could not open input file.\n", 1;

  std::vector<int> list1, list2;
  for (int num1, num2; inputFile >> num1 >> num2; list1.push_back(num1), list2.push_back(num2));

  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());

  std::cout << std::inner_product(list1.begin(), list1.end(), list2.begin(), 0, std::plus<>(), [](int a, int b) { return std::abs(a - b); }) << '\n';
}
