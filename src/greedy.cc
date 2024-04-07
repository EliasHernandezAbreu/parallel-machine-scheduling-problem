/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents the greedy PMSP algorithm
 */

#include "../lib/greedy.h"

Solution Greedy::solve(const Problem *problem) const {
  Solution result(problem);
  for (int task = 1; task <= problem->getTaskAmount(); task++) { // start in task 1 because task 0 is dumb
    int machine_index;
    int position;
    int increment;
    increment = result.bestInsert(task, &machine_index, &position);
    result.addTask(machine_index, task, position, increment);
  }
  return result;
}
