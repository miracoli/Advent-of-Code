#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>

int main() {
  std::ifstream inf{"input.txt"};
  if (!inf) {
    std::cerr << "Could not open file: input.txt \n";
    return 2;
  }

  for (std::string line; std::getline(inf, line) && !line.empty(););

  std::vector<std::string> as, bs, cs, ds, wrong;
  std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> gates;
  for (std::string input1, input2, op, out, _; inf >> input1 >> op >> input2 >> _ >> out; gates[out] = {op, input1, input2}) {
    if ((input1[0] == 'x' && input2[0] == 'y') || (input1[0] == 'y' && input2[0] == 'x')) {
      int n1{std::stoi(input1.substr(1))}, n2{std::stoi(input2.substr(1))};

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

  auto gateSwap = [&](const std::string in1, const std::string in2) {
    std::swap(gates[in2], gates[in1]);
    for (auto* vec : {&as, &bs, &cs, &ds}) {
      for (auto& output : *vec) {
        if (output == in2 || output == in1) {
          output = (output == in2) ? in1 : in2;
        }
      }
    }
  };

  auto findGateOutputs = [&](int i) {
    for (const auto &[out_gate, gate_gate] : gates) {
      if (ds[i].empty() && std::get<0>(gate_gate) == "AND" && ((as[i - 1] == std::get<1>(gate_gate) && cs[i - 1] == std::get<2>(gate_gate)) || (as[i - 1] == std::get<2>(gate_gate) && cs[i - 1] == std::get<1>(gate_gate)))) {
        ds[i] = out_gate; break;
      } else if (!ds[i].empty() && cs[i].empty() && std::get<0>(gate_gate) == "OR" && ((bs[i - 1] == std::get<1>(gate_gate) && ds[i] == std::get<2>(gate_gate)) || (bs[i - 1] == std::get<2>(gate_gate) && ds[i] == std::get<1>(gate_gate)))) {
        cs[i] = out_gate; break;
      } else if (!cs[i].empty() && std::get<0>(gate_gate) == "XOR" && ((as[i] == std::get<1>(gate_gate) && cs[i] == std::get<2>(gate_gate)) || (as[i] == std::get<2>(gate_gate) && cs[i] == std::get<1>(gate_gate)))) {
        return out_gate;
      }
    }
    return std::string{};
  };

  auto gate = gates.at("z00");
  std::string& in1 = std::get<1>(gate), &in2 = std::get<2>(gate);
  if (std::get<0>(gate) != "XOR" || !((in1 == "x00" && in2 == "y00") || (in1 == "y00" && in2 == "x00"))) {
    wrong.push_back("z00");
  }

  for (int i = 1; i < as.size(); ++i) {
    std::string label = std::string("z") + (i < 10 ? "0" : "") + std::to_string(i);
    gate = gates.at(label);
    in1 = std::get<1>(gate), in2 = std::get<2>(gate);

    if (std::get<0>(gate) != "XOR") { // wrong operation
      ds[i] = cs[i] = "";
      std::string labelSwap;
      while(labelSwap.empty()) {
        labelSwap = findGateOutputs(i);
      }
      wrong.insert(wrong.end(), {labelSwap, label});
      gateSwap(label, labelSwap);
    } else if (in1 != as[i] && in2 != as[i]) { // XOR gate with wrong inputs
      wrong.push_back(as[i]);
      gateSwap(as[i], (std::get<1>(gates.at(in1)) == bs[i - 1] || std::get<2>(gates.at(in1)) == bs[i - 1]) ? in2 : in1);
      wrong.push_back(as[i]);
    }

    while(cs[i].empty()) {
      findGateOutputs(i);
    }
  }

  std::sort(wrong.begin(), wrong.end());

  for (auto i = 0; i < wrong.size(); ++i) {
    std::cout << wrong[i] << (i < wrong.size()-1 ? "," : "");
  }
}
