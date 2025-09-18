#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <numeric>

int main() {
  std::ifstream file("input.txt");
  if (!file) {
    std::cerr << "Error: Could not open input file.\n";
    return 1;
  }

  std::vector<int> list1;
  std::unordered_map<int, int> freq;

  for (int a, b; file >> a >> b; list1.push_back(a), ++freq[b]);

  std::cout << std::accumulate(list1.begin(), list1.end(), 0, [&freq](int sum, int num) { return sum + num * freq[num]; }) << '\n';
}
