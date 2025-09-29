#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

int main() {
  ifstream input("input.txt");
  if (!input) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }
  unordered_map<string, unordered_set<string>> connections;

  for (string a, b; getline(input, a, '-') && getline(input, b);) {
    if(a < b) {
      connections[a].insert(b);
    } else {
      connections[b].insert(a);
    }
  }

  int count = 0;

  for (const auto& [node, neighbors] : connections) {
    for (const auto& neighbor : neighbors) {
      for (const auto& common : connections[neighbor]) {
        if (connections[node].contains(common) && (node[0] == 't' || neighbor[0] == 't' || common[0] == 't')) {
          ++count;
        }
      }
    }
  }

  cout << count << endl;
}
