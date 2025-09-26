#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

static const unordered_map<char, pair<int, int>> deltas = {{'<', {-1, 0}}, {'>', {1, 0}}, {'^', {0, -1}}, {'v', {0, 1}}};
vector<string> grid;
pair<int, int> robot;
int gpsSum = 0;

bool moveBox(const pair<int, int>& box, const pair<int, int>& delta) {
  if (auto newBox = pair<int, int>{box.first + delta.first, box.second + delta.second};
      grid[newBox.second][newBox.first] == '.' ||
          (grid[newBox.second][newBox.first] == 'O' && moveBox(newBox, delta))) {
    gpsSum += 100 * delta.second + delta.first;
    grid[newBox.second][newBox.first] = 'O';
    return true;
  }
  return false;
}

int main() {
  ifstream input("input.txt");
  if (!input) {
    cerr << "Error: input.txt not found" << endl;
    return 1;
  }
  for (string line; getline(input, line) && !line.empty(); grid.emplace_back(std::move(line))) {
    for (int x = 0; x < line.size(); ++x) {
      if (line[x] == '@') {
        robot = {x, static_cast<int>(grid.size())};
      } else if (line[x] == 'O') {
        gpsSum += 100 * (grid.size() ) + x;
      }
    }
  }

  for (string line; getline(input, line) && !line.empty();) {
    for (char move : line) {
      auto [dx, dy] = deltas.at(move);
      pair<int, int> newRobot = {robot.first + dx, robot.second + dy};
      if ((grid[newRobot.second][newRobot.first] == 'O' && moveBox(newRobot, {dx, dy})) || grid[newRobot.second][newRobot.first] == '.') {
        grid[newRobot.second][newRobot.first] = '@';
        grid[robot.second][robot.first] = '.';
        robot = newRobot;
      }
    }
  }

  cout << gpsSum << endl;
}
