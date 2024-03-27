/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents the greedy PMSP algorithm
 */

#include <cstdio>
#include <vector>

#include "../lib/greedy.h"

Solution GreedyPMSP::solve(const Problem *problem) const {
  Solution result(problem);
  for (int task = 1; task <= problem->getTaskAmount();
       task++) { // start in task 1 because task 0 is dumb
    printf("check task %d\n", task);
    int best_machine = 0;
    int best_position = 0;
    int best_tct = 9999999;
    for (int current_machine = 0; current_machine < problem->getMachineAmount();
         current_machine++) {
      printf("check machine %d\n", current_machine);
      std::vector<int> machine_tasks = result.getTasks(current_machine);
      for (int position = 0; position < machine_tasks.size(); position++) {
        printf("check position %d\n", position);
        int current_tct =
            result.testAddTaskTCT(current_machine, task, position);
        if (current_tct > best_tct)
          continue;
        best_tct = current_tct;
        best_position = position;
        best_machine = current_machine;
      }
    }
    printf("ended greedy\n");
    result.addTask(best_machine, task, best_position);
  }
  return result;
}
