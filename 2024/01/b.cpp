#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <numeric>
using namespace std;

int main() {
  ifstream file("input.txt");
  if (!file) {
    cerr << "Error: Could not open input file." << endl;
    return 1;
  }

  vector<int> list1;
  unordered_map<int, int> freq;

  int a;
  int b;
  while (file >> a >> b) {
    list1.push_back(a);
    ++freq[b];
  }

  cout << accumulate(list1.begin(), list1.end(), 0, [&freq](int sum, int num) {
           return sum + num * freq[num];
         })
       << endl;
}
