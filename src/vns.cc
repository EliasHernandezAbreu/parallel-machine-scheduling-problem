/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents the vns pmsp algorithm
 */

#include "../lib/vns.h"
#include "../lib/solution.h"

Solution Vns::solve(const Problem* problem) const {
  Solution best_solution;
  best_solution = constructivePhase(problem);
  int worse_solution_counter = 0;
  for (int repetition = 0; repetition < repetitions; repetition++) {
    if (worse_solution_counter > repetitions / 5) break;
    worse_solution_counter++;
    Solution current_solution;
    current_solution = constructivePhase(problem);
    current_solution.vnd();
    for (int move_length = 1; move_length <= max_length; move_length++) {
      Solution new_solution(current_solution);
      new_solution.perturbate(move_length);
      new_solution.vnd();
      if (new_solution.getTotalTCT() < current_solution.getTotalTCT()) {
        current_solution = new_solution;
        move_length = 1;
      }
    }
    if (current_solution.getTotalTCT() < best_solution.getTotalTCT()) {
      best_solution = current_solution;
      worse_solution_counter = 0;
    }
  }
  return best_solution;
}
