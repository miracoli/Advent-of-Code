#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <deque>
#include <string>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  string line;
  if (!getline(inputFile, line)) {
    cerr << "Error opening/reading file." << endl;
    return 1;
  }

  long long checksum = 0;
  long long start = 0;
  vector<tuple<long long, int, int>> disk; // start, size, index
  deque<int> freeBlocks; // indices of free blocks

  for (int id = 0, i = 0, len; i < (int)line.size(); start += len, ++i) {
        len = line[i] - '0';
    if (!(i & 1)) {
      checksum += id * start * len + id * len * (len - 1) / 2;
    } else {
      freeBlocks.push_back((int)disk.size());
    }
    disk.emplace_back(start, len, i & 1 ? -1 : id++);
  }

  for (int usedIdx = (int)disk.size() - 1; usedIdx >= 1; --usedIdx) {
    if (get<2>(disk[usedIdx]) != -1) {
      for (auto it = freeBlocks.begin(); it != freeBlocks.end(); ++it) {
        int freeIdx = *it;
        if (freeIdx >= usedIdx) {
          break;
        }
        if (get<1>(disk[freeIdx]) >= get<1>(disk[usedIdx])) {
          int diff = get<1>(disk[usedIdx]);
          checksum += get<2>(disk[usedIdx]) * diff * (get<0>(disk[freeIdx]) - get<0>(disk[usedIdx]));
          get<1>(disk[freeIdx]) -= diff;
          get<0>(disk[freeIdx]) += diff;

          if (get<1>(disk[freeIdx]) == 0) {
            freeBlocks.erase(it);
          }
          break;
        }
      }
    }
  }

  cout << checksum << endl;
}
