#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <array>

using namespace std;

static constexpr std::array<int, 2> dirFactors{-1, 1};

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Failed to open input.txt";
        return 1;
    }

    map<char, vector<pair<int, int>>> antennas;
    int rows = 0;
    int cols;
    set<pair<int, int>> antinodes;

    for (string line; getline(inputFile, line); ) {
        cols = static_cast<int>(line.size());
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] != '.') {
                antennas[line[x]].emplace_back(x, rows);
            }
        }
        ++rows;
    }

    for (const auto& [freq, positions] : antennas) {
        for (size_t i = 0; i < positions.size(); ++i) {
            for (size_t j = i + 1; j < positions.size(); ++j) {
                int dx = positions[j].first - positions[i].first;
                int dy = positions[j].second - positions[i].second;
                for (int dir : dirFactors) {
                    for (int a = 0; ; ++a) {
                        pair<int, int> p = { positions[i].first + dir * a * dx, positions[i].second + dir * a * dy };
                        if (p.first >= 0 && p.second >= 0 && p.first < cols && p.second < rows) {
                            antinodes.insert(p);
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }

    cout << antinodes.size() << endl;
}
