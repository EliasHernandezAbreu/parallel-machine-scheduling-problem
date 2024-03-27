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
#include "../lib/utils.h"

#include <cstdio>
#include <vector>

Solution::Solution(const Problem *problem) {
  machine_tasks = new std::vector<int>[problem->getMachineAmount()];
  for (int i = 0; i < problem->getMachineAmount(); i++) {
    machine_tasks[i].reserve(problem->getTaskAmount());
    machine_tasks[i].push_back(0); // All machines start with task 0
  }
  original_problem = problem;
}

int Solution::testAddTaskTCT(int machine, int task, int position) const {
  std::vector<int> test_machine = machine_tasks[machine];
  printf("test add task tct machine %d, task %d, position %d\n", machine, task,
         position);
  test_machine.emplace(test_machine.begin() + position + 1, task);
  printf("test add task tct machine %d, task %d, position %d\n", machine, task,
         position);
  int resulting_tct =
      getMachineTCT(test_machine, original_problem->getChangeCosts());

  return resulting_tct;
}

void Solution::addTask(int machine, int task, int position) {
  printf("add task tct machine %d, task %d, position %d\n", machine, task,
         position);
  if (machine_tasks[machine].size() == position) {
    machine_tasks[machine].push_back(task);
  } else {
    machine_tasks[machine].emplace(machine_tasks->begin() + position + 1, task);
  }
  printf("add task tct machine %d, task %d, position %d\n", machine, task,
         position);
}

const std::vector<int> &Solution::getTasks(int machine) const {
  return machine_tasks[machine];
}
