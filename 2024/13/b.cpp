#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

int main() {
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string content((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    regex rx(R"(Button A: X([+-]?\d+), Y([+-]?\d+)\nButton B: X([+-]?\d+), Y([+-]?\d+)\nPrize: X=([+-]?\d+), Y=([+-]?\d+))");
    
    int64_t res = 0;
    for (sregex_iterator it(content.begin(), content.end(), rx), end; it != end; ++it) {
        auto& m = *it;
        int64_t ax = stoi(m[1]);
        int64_t ay = stoi(m[2]);
        int64_t bx = stoi(m[3]);
        int64_t by = stoi(m[4]);
        int64_t X = stoll(m[5]) + 10000000000000;
        int64_t Y = stoll(m[6]) + 10000000000000;
        int64_t b = (Y * ax - X * ay) / (by * ax - bx * ay);
        int64_t a = (X - b * bx) / ax;
        if (a * ax + b * bx == X && a * ay + b * by == Y) {
            res += 3 * a + b;
        }
    }

    cout << res << endl;
}
