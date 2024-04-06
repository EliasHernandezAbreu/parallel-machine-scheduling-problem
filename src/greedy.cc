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

Solution Greedy::solve(const Problem *problem) const {
  Solution result(problem);
  for (int task = 1; task <= problem->getTaskAmount(); task++) { // start in task 1 because task 0 is dumb
    int best_machine = 0;
    int best_position = 0;
    int best_tct = 9999999;

    for (int current_machine = 0; current_machine < problem->getMachineAmount(); current_machine++) {
      const std::vector<int>& machine_tasks = result.getTasks(current_machine);

      for (int position = 0; position <= machine_tasks.size(); position++) {
        int current_tct =  result.testAddTaskTCT(current_machine, task, position) - result.getMachineTCT(current_machine);
        if (current_tct >= best_tct) continue;
        best_tct = current_tct;
        best_position = position;
        best_machine = current_machine;
      }
    }
    result.addTask(best_machine, task, best_position);
    result.printMachine(best_machine);
    printf("task: %d, machine: %d, position: %d, tct got %d, confirmed %d\n",
           task, best_machine, best_position,
           result.getMachineTCT(best_machine),
           result.getConfirmedSlowMachineTCT(best_machine));
  }
  return result;
}
