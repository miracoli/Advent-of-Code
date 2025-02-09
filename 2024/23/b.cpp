#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_map<string, unordered_set<string>> connections;
unordered_set<string> largestClique;

void findLargestClique(unordered_set<string>& R, unordered_set<string>& P, unordered_set<string>& X) {
  if (P.empty() && X.empty() && R.size() > largestClique.size()) {
    largestClique = R;
    return;
  }

  if (R.size() + P.size() <= largestClique.size()) {
    return;
  }

  unordered_set<string> P_copy = P;
  for (const auto& v : P_copy) {
    unordered_set<string> R_new = R, P_new, X_new;
    R_new.insert(v);

    for (const auto& p : P) {
      if (connections[v].count(p)) {
        P_new.insert(p);
      }
    }
    for (const auto& x : X) {
      if (connections[v].count(x)) {
        X_new.insert(x);
      }
    }

    findLargestClique(R_new, P_new, X_new);

    P.erase(v);
    X.insert(v);
  }
}

int main() {
  ifstream input{"input.txt"};
  unordered_set<string> computers;

  for (string a, b; getline(input, a, '-') && getline(input, b);) {
    computers.insert(a);
    computers.insert(b);
    connections[a].insert(b);
    connections[b].insert(a);
  }

  unordered_set<string> R, X;
  findLargestClique(R, computers, X);

  vector<string> result(largestClique.begin(), largestClique.end());
  sort(result.begin(), result.end());

  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i] << (i < result.size() - 1 ? "," : "\n");
  }
}
