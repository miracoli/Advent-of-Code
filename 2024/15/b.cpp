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

bool moveBox(const pair<int, int>& box, const pair<int, int>& delta, bool simulate = false) {
    auto move = [&](const pair<int, int>& p) {
        if (grid[p.second][p.first] == '.' || (grid[p.second][p.first] == '[' || grid[p.second][p.first] == ']') && moveBox(p, delta, simulate)) {
            if (!simulate) {
                swap(grid[p.second][p.first], grid[box.second][delta.second ? p.first : box.first]);
                if(grid[p.second][p.first] == '[') {
                  gpsSum += 100 * delta.second + delta.first; 
                }
            }
            return true;
        }
        return false;
    };

    if (delta.second) { // vertical move
       pair<int, int> newBoxR = {box.first + delta.first + (grid[box.second][box.first] == '['), box.second + delta.second};
       pair<int, int> newBoxL = {box.first + delta.first - (grid[box.second][box.first] != '['), box.second + delta.second};
       return move(newBoxL) && move(newBoxR);
    } 
    return move({box.first + delta.first, box.second + delta.second}); // horizontal move
}

int main() {
  ifstream input("input.txt");
  if (!input) return cerr << "Error: input.txt not found\n", 1;

  for (string line; getline(input, line) && !line.empty(); grid.emplace_back(move(line))) {
    for (size_t x = 0; x < line.size(); x += 2) {
      line.replace(x, 1, (line[x] == 'O') ? (gpsSum += 100 * grid.size() + x, "[]") : (line[x] == '@') ? (robot = {x, (int)grid.size()}, "@.") : string(2, line[x]));
    }
  }

    for (string line; getline(input, line);) {
        for (char move : line) {
            auto [dx, dy] = deltas.at(move);
            pair<int, int> newRobot = {robot.first + dx, robot.second + dy};

            char &target = grid[newRobot.second][newRobot.first];
            if ((target == '[' || target == ']') ? moveBox(newRobot, {dx, dy}, true) && moveBox(newRobot, {dx, dy}) : target == '.') {
              swap(target, grid[robot.second][robot.first]);
              robot = newRobot;
            }
        }
    }

    cout << gpsSum << endl;
}
