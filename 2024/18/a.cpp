#include <iostream>
#include <queue>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <array>

using namespace std;

constexpr std::array<int, 4> DIRECTIONS{0, 1, 0, -1};
std::array<std::array<int, 71>, 71> dist{};
queue<pair<int, int>> positions({{0, 0}});

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input.txt" << endl;
        return 1;
    }

    int xCoord, yCoord, maxCount = 0;
    std::array<std::array<bool, 71>, 71> grid{};

    for (string line; getline(inputFile, line) && maxCount < 1024; ++maxCount) {
        replace(line.begin(), line.end(), ',', ' ');
        if (stringstream(line) >> xCoord >> yCoord) {
            grid[xCoord][yCoord] = true;
        }
    }

    for (auto& row : dist) {
        row.fill(-1);
    }
    dist[0][0] = 0;
    while (!positions.empty()) {
        auto [xCoord, yCoord] = positions.front(); positions.pop();
        if (xCoord == 70 && yCoord == 70) {
            cout << dist[xCoord][yCoord] << endl;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = xCoord + DIRECTIONS[i], newY = yCoord + DIRECTIONS[(i + 3) & 3];
            if (newX >= 0 && newX < 71 && newY >= 0 && newY < 71 && !grid[newX][newY] && dist[newX][newY] == -1) {
                dist[newX][newY] = dist[xCoord][yCoord] + 1;
                positions.push({newX, newY});
            }
        }
    }
}
