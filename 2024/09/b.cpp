#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  string line;
  if (!getline(inputFile, line)) return cerr << "Error opening/reading file.\n", 1;

  long long checksum = 0, start = 0;
  vector<tuple<long long, int, int>> disk; // start, size, index
  for (int id = 0, i = 0, len; i < line.size() && (len = line[i] - '0', true); start += len, ++i) {
    if(!(i&1)) {
      checksum += id * start * len + id * len * (len - 1) / 2;
    }
    disk.emplace_back(start, len, i & 1 ? -1 : id++);
  }

  for (int usedIdx = disk.size() - 1; usedIdx >= 1; --usedIdx) {
    if (get<2>(disk[usedIdx]) != -1) {
      for (int freeIdx = 0; freeIdx < usedIdx; ++freeIdx) {
        if (get<2>(disk[freeIdx]) == -1 && get<1>(disk[freeIdx]) >= get<1>(disk[usedIdx])) {
          int diff = get<1>(disk[usedIdx]);
          checksum += get<2>(disk[usedIdx]) * diff * (get<0>(disk[freeIdx]) - get<0>(disk[usedIdx]));
          get<1>(disk[freeIdx]) -= diff;
          get<0>(disk[freeIdx]) += diff;
          break;
        }
      }
    }
  }

  cout << checksum << endl;
}