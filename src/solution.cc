/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Solution for a PMSP problem
 */

#include "../lib/solution.h"
#include <vector>

Solution::Solution(const Problem &problem) {
  machine_tasks = new std::vector<int>[problem.getMachineAmount()];
}
