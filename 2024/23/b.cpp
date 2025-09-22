#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

vector<unordered_set<int>> connections;
unordered_set<int> largestClique;

void findLargestClique(unordered_set<int>& R, unordered_set<int>& P, unordered_set<int>& X) {
  if (P.empty() && X.empty() && R.size() > largestClique.size()) {
    largestClique = R;
    return;
  }
  if (R.size() + P.size() <= largestClique.size()) {
    return;
  }

  unordered_set<int> P_copy = P;
  for (int v : P_copy) {
    unordered_set<int> R_new = R, P_new, X_new;
    R_new.insert(v);

    for (int p : P) {
      if (connections[v].contains(p)) {
        P_new.insert(p);
      }
    }
    for (int x : X) {
      if (connections[v].contains(x)) {
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

  unordered_map<string,int> id;
  vector<string> name;

  auto getId = [&id, &name](const string& s) -> int {
    auto [it, added] = id.try_emplace(s, (int)id.size());
    if (added) name.push_back(s);
    return it->second;
  };

  vector<pair<int,int>> edges;
  string a, b;
   while (getline(input, a, '-') && getline(input, b)) {
    int u = getId(a), v = getId(b);
    if (u != v) edges.emplace_back(u, v);
  }

  int n = (int)name.size();
  connections.assign(n, {});
  for (auto [u, v] : edges) {
    connections[u].insert(v);
    connections[v].insert(u);
  }

  unordered_set<int> R, P, X;
  for (int i = 0; i < n; ++i) {
    P.insert(i);
  }
  findLargestClique(R, P, X);

  vector<string> result;
  for (int v : largestClique) {
    result.push_back(name[v]);
  }
  sort(result.begin(), result.end());

  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i] << (i + 1 < result.size() ? "," : "");
  }
  cout << endl;
}
