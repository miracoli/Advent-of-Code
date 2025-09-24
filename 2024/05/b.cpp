#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Error opening file." << endl;
    return 1;
  }

  unordered_map<int, unordered_set<int>> rules;

  for (string line; getline(inputFile, line) && line.contains('|');) {
    int from;
    int to;
    char delim; 
    stringstream(line) >> from >> delim >> to;
    rules[from].insert(to);
  }

  int middleSum = 0;
  for (string line; getline(inputFile, line);) {
    stringstream ss(line);
    vector<int> seq;
    unordered_set<int> pos;
    bool isInvalid = false;

    for (int n; ss >> n; ss.ignore(1, ',')) {
      if (!isInvalid && !ranges::all_of(rules[n], [&pos](int to) { return !pos.contains(to); })) {
        isInvalid = true;
      }
      seq.push_back(n);
      pos.insert(n);
    }
    if(isInvalid) {
      ranges::stable_sort(seq, [&rules](int a, int b) { return rules[a].contains(b); });
      middleSum += seq[seq.size() / 2];
    }
  }

  cout << middleSum << endl;
}
