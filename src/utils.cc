/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Solution for a PMSP problem
 */

#include "../lib/utils.h"
#include <string>

int getMachineTCT(const std::vector<int> &machine, int const *const *const change_costs) {
  int result = 0;
  for (int i = 1; i < machine.size(); i++) {
    int work = 0;
    work += change_costs[machine[i - 1]][machine[i]];
    work *= machine.size() - i;
    result += work;
  }
  return result;
}

std::string printMachine(const std::vector<int> &machine) {
  std::string result = "INIT";
  for (int i = 1; i < machine.size(); i++) {
    result += " -> " + std::to_string(machine[i]);
  }
  return result;
}
