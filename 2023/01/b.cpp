#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <string_view>
#include <string>

using namespace std;

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) {
    cerr << "Error: Could not open input file.\n";
    return 1;
  }

  constexpr array<string_view, 9> words{ "one","two","three","four","five","six","seven","eight","nine" };
  uint64_t sum = 0;

  auto checkAt = [&](const string& line, size_t i, int& target) {
    char c = line[i];
    if (isdigit(static_cast<unsigned char>(c))) {
        target = c - '0';
        return;
    }
    string_view sv(line.c_str() + i, line.size() - i);
    for (int d = 0; d < static_cast<int>(words.size()); ++d) {
      if (sv.starts_with(words[d])) {
        target = d + 1;
        return;
      }
    }
  };

  for (string line; getline(inputFile, line); ) {
    int firstDigit = -1;
    int lastDigit  = -1;

    for (size_t i = 0; i < line.size() && firstDigit == -1; ++i) { // left-to-right
      checkAt(line, i, firstDigit);
    }

    for (size_t i = line.size() - 1; i >= 0 && lastDigit == -1; --i) { // right-to-left
      checkAt(line, i, lastDigit);
    }

    if (firstDigit != -1) {
      sum += firstDigit * 10 + lastDigit;
    }
  }

  cout << sum << endl;
}
