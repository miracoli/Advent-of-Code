#include <iostream>
#include <queue>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

constexpr int DIRECTIONS[] = { 0, 1, 0, -1 };
int dist[71][71];

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input.txt" << endl;
        return 1;
    }

    int xCoord, yCoord, maxCount = 0;
    bool grid[71][71] = {}, solvable = true;

    for (string line; getline(inputFile, line) && solvable; ++maxCount) {
        replace(line.begin(), line.end(), ',', ' ');
        if (stringstream(line) >> xCoord >> yCoord) {
            grid[xCoord][yCoord] = true;
        }
        if(maxCount < 1024) {
          continue;
        }
        fill(&dist[0][0], &dist[70][71], -1);
        dist[0][0] = 0;
        solvable = false;
        queue<pair<int, int>> positions({{0, 0}});
        while (!positions.empty()) {
            auto [xCoord, yCoord] = positions.front();
            positions.pop();
            if (xCoord == 70 && yCoord == 70) {
                solvable = true;
                break;
            }

            for (int i = 0; i < 4; ++i) {
                int newX = xCoord + DIRECTIONS[i], newY = yCoord + DIRECTIONS[(i + 3) & 3];
                if (newX >= 0 && newX < 71 && newY >= 0 && newY < 71 && !grid[newX][newY] && dist[newX][newY] == -1) {
                    dist[newX][newY] = dist[xCoord][yCoord] + 1;
                    positions.emplace(newX, newY);
                }
            }
        }
    }
    cout << xCoord << "," << yCoord << endl;
}
