/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents the grasp PMSP algorithm
 */

#include "../lib/grasp.h"

Grasp::Grasp(int best_solution_size, int repetitions) {
  this->best_solutions_size = best_solution_size;
  this->repetitions = repetitions;
}

Solution Grasp::constructivePhase(const Problem* problem) const {
  // Create lists to store best results for each task
  int best_machines[best_solutions_size];
  int best_positions[best_solutions_size];
  int best_increments[best_solutions_size];
  // Create list of results
  Solution result[repetitions];
  for (int r = 0; r < repetitions; r++) {
    result[r].fromProblem(problem);
    // Loop each task
    for (int task = 1; task <= problem->getTaskAmount(); task++) {
      result[r].bestInsert(task, best_increments, best_machines, best_positions, best_solutions_size);
      // Choose a random element from the best ones
      int chosen_index = rand() % best_solutions_size;
      int chosen_machine = best_machines[chosen_index];
      int chosen_position = best_positions[chosen_index];
      int chosen_increment = best_increments[chosen_index];
      result[r].addTask(chosen_machine, task, chosen_position, chosen_increment);
    }
  }
  // Get best result
  int best_result_index = 0;
  int best_result_tct = 9999999;
  for (int r = 0; r < repetitions; r++) {
    int current_result_tct = result[r].getTotalTCT();
    if (current_result_tct < best_result_tct) {
      best_result_tct = current_result_tct;
      best_result_index = r;
    }
  }
  Solution final_result(result[best_result_index]);
  return final_result;
}

int Grasp::improveSolution(Solution* solution) const {
  return 0;
}

Solution Grasp::solve(const Problem *problem) const {
  Solution result(constructivePhase(problem));
  float previous_tct = result.getTotalTCT();
  while (improveSolution(&result) < 0) {}
  float improvement = (previous_tct - result.getTotalTCT()) / previous_tct;
  // printf("\nSolution improved by %f%%\n", improvement);
  return result;
}

