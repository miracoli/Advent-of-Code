#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  ifstream inf{"input.txt"};
  if (!inf) {
    cerr << "Could not open file: input.txt" << endl;
    return 1;
  }

  for (string line; getline(inf, line) && !line.empty(););

  vector<string> as, bs, cs, ds, wrong;
  unordered_map<string, tuple<string, string, string>> gates;
  for (string input1, input2, op, out, _; inf >> input1 >> op >> input2 >> _ >> out; gates[out] = {op, input1, input2}) {
    if ((input1[0] == 'x' && input2[0] == 'y') || (input1[0] == 'y' && input2[0] == 'x')) {
      int n1{stoi(input1.substr(1))}, n2{stoi(input2.substr(1))};

      if (n1 == n2) {
        if (n1 + 1 > as.size()) {
          as.resize(n1 + 1);
          bs.resize(n1 + 1);
        }

        as[n1] = (op == "XOR") ? out : as[n1];
        bs[n1] = (op == "AND") ? out : bs[n1];
      }
    }
  }
  cs.resize(as.size());
  ds.resize(as.size());
  cs[1] = bs[0]; // Initialize first carry signal

  auto gateSwap = [&gates, &as, &bs, &cs, &ds](const string in1, const string in2) {
    swap(gates[in2], gates[in1]);
    for (auto* vec : {&as, &bs, &cs, &ds}) {
      for (auto& output : *vec) {
        if (output == in2 || output == in1) {
          output = (output == in2) ? in1 : in2;
        }
      }
    }
  };

  auto findGateOutputs = [&gates, &ds, &as, &cs, &bs](int i) {
    for (const auto &[out_gate, gate_gate] : gates) {
      if (ds[i].empty() && get<0>(gate_gate) == "AND" && ((as[i - 1] == get<1>(gate_gate) && cs[i - 1] == get<2>(gate_gate)) || (as[i - 1] == get<2>(gate_gate) && cs[i - 1] == get<1>(gate_gate)))) {
        ds[i] = out_gate; break;
      } else if (!ds[i].empty() && cs[i].empty() && get<0>(gate_gate) == "OR" && ((bs[i - 1] == get<1>(gate_gate) && ds[i] == get<2>(gate_gate)) || (bs[i - 1] == get<2>(gate_gate) && ds[i] == get<1>(gate_gate)))) {
        cs[i] = out_gate; break;
      } else if (!cs[i].empty() && get<0>(gate_gate) == "XOR" && ((as[i] == get<1>(gate_gate) && cs[i] == get<2>(gate_gate)) || (as[i] == get<2>(gate_gate) && cs[i] == get<1>(gate_gate)))) {
        return out_gate;
      }
    }
    return string{};
  };

  auto gate = gates.at("z00");
  string& in1 = get<1>(gate), &in2 = get<2>(gate);
  if (get<0>(gate) != "XOR" || !((in1 == "x00" && in2 == "y00") || (in1 == "y00" && in2 == "x00"))) {
    wrong.emplace_back("z00");
  }

  for (int i = 1; i < as.size(); ++i) {
    string label = string("z") + (i < 10 ? "0" : "") + to_string(i);
    gate = gates.at(label);
    in1 = get<1>(gate), in2 = get<2>(gate);

    if (get<0>(gate) != "XOR") { // wrong operation
      ds[i] = cs[i] = "";
      string labelSwap;
      while(labelSwap.empty()) {
        labelSwap = findGateOutputs(i);
      }
      wrong.insert(wrong.end(), {labelSwap, label});
      gateSwap(label, labelSwap);
    } else if (in1 != as[i] && in2 != as[i]) { // XOR gate with wrong inputs
      wrong.push_back(as[i]);
      gateSwap(as[i], (get<1>(gates.at(in1)) == bs[i - 1] || get<2>(gates.at(in1)) == bs[i - 1]) ? in2 : in1);
      wrong.push_back(as[i]);
    }

    while(cs[i].empty()) {
      findGateOutputs(i);
    }
  }

  ranges::sort(wrong);

  std::cout << std::ranges::to<std::string>(wrong | std::views::join_with(',')) << std::endl;
}
