#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
using namespace std;

int main() {
  ifstream inputFile("input.txt", ios::binary);
  if (!inputFile) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }
  vector<int> disk;
  uint64_t idx = 0;
  int id = 0;
  uint64_t checksum = 0;
  for (istreambuf_iterator<char> it(inputFile), end; it != end; ++it, ++idx) {
    disk.insert(disk.end(), *it - '0', idx & 1 ? -1 : id++);
  }

  for (int freeIdx = 0, usedIdx = static_cast<int>(disk.size()) - 1; freeIdx <= usedIdx; --usedIdx) {
    if(disk[usedIdx] != -1) {
      while (disk[freeIdx] != -1 && freeIdx <= usedIdx) {
        checksum += freeIdx * disk[freeIdx];
        ++freeIdx;
      }

      if (freeIdx < usedIdx) {
        checksum += freeIdx++ * disk[usedIdx]; // Update checksum for swapped values
      }
    }
  }
  
  cout << checksum << endl;
}
