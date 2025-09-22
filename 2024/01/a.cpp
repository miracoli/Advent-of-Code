#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Error: Could not open input file." << endl;
    return 1;
  }

  vector<int> list1;
  vector<int> list2;

  int num1;
  int num2;
  while (inputFile >> num1 >> num2) {
    list1.push_back(num1);
    list2.push_back(num2);
  }

  ranges::sort(list1);
  ranges::sort(list2);

  cout << inner_product(list1.begin(), list1.end(), list2.begin(), 0, plus<>(),
                        [](int a, int b) { return abs(a - b); })
       << endl;
}
