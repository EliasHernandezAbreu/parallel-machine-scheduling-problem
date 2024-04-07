/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents the grasp PMSP algorithm
 */

#include <cstdlib>
#include <vector>

#include "../lib/grasp.h"

Grasp::Grasp(int best_solution_size, int repetitions) {
  this->best_solutions_size = best_solution_size;
  this->repetitions = repetitions;
}

Solution Grasp::solve(const Problem *problem) const {
  /*
  // Create lists to store best results for each task
  int best_machines[best_solutions_size];
  int best_positions[best_solutions_size];
  int best_increments[best_solutions_size];
  // Create list of results
  Solution result[repetitions];
  for (int r = 0; r < repetitions; r++) {
    result[r].ChangeProblem(problem);
    // Loop each task
    for (int task = 1; task <= problem->getTaskAmount(); task++) {
      // Reset the lists to their original values
      int worst_best_index = 0;
      int worst_best_increment = 9999999;
      for (int i = 0; i < best_solutions_size; i++) {
        best_machines[i] = 0;
        best_positions[i] = 0;
        best_increments[i] = 9999999;
      }
      // Loop each machine
      for (int current_machine = 0; current_machine < problem->getMachineAmount(); current_machine++) {
        // Loop each position of the machine
        std::vector<int> machine_tasks = result[r].getTasks(current_machine);
        for (int position = 0; position <= machine_tasks.size(); position++) {
          int current_increment = result[r].testAddTaskIncrement(current_machine, task, position);
          // Change the lists element to the new one (if its better)
          if (current_increment < worst_best_increment) {
            best_increments[worst_best_index] = current_increment;
            best_machines[worst_best_index] = current_machine;
            best_positions[worst_best_index] = position;
            worst_best_increment = current_increment;
            // Get the index of the task to change in the list of bests
            for (int i = 0; i < best_solutions_size; i++) {
              if (best_increments[i] > worst_best_increment) {
                worst_best_increment = best_increments[i];
                worst_best_index = i;
              }
            }
          }
        }
      }
      // Choose a random element from the best ones
      int chosen_index = rand() % best_solutions_size;
      int chosen_machine = best_machines[chosen_index];
      int chosen_position = best_positions[chosen_index];
      result[r].addTask(chosen_machine, task, chosen_position);
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
  Solution final_result;
  final_result = result[best_result_index];
  return final_result;
  */
  return 0;
}

