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

#include <vector>

Solution::Solution(const Problem *problem) {
  machine_tasks = new std::vector<int>[problem->getMachineAmount()];
  for (int i = 0; i < problem->getMachineAmount(); i++) {
    machine_tasks[i].reserve(problem->getTaskAmount());
    machine_tasks[i].push_back(0); // All machines start with task 0
  }
  original_problem = problem;
}

Solution::Solution() {
  machine_tasks = nullptr;
  original_problem = nullptr;
}

void Solution::ChangeProblem(const Problem *problem) {
  if (machine_tasks != nullptr) {
    delete[] machine_tasks;
  }
  machine_tasks = new std::vector<int>[problem->getMachineAmount()];
  for (int i = 0; i < problem->getMachineAmount(); i++) {
    machine_tasks[i].reserve(problem->getTaskAmount());
    machine_tasks[i].push_back(0); // All machines start with task 0
  }
  original_problem = problem;
}

int Solution::testAddTaskTCT(int machine, int task, int position) const {
  std::vector<int> test_machine = machine_tasks[machine];
  test_machine.emplace(test_machine.begin() + position + 1, task);
  int resulting_tct = getMachineTCT(test_machine, original_problem->getChangeCosts());

  return resulting_tct;
}

void Solution::addTask(int machine, int task, int position) {
  machine_tasks[machine].emplace(machine_tasks[machine].begin() + position + 1, task);
}

const std::vector<int> &Solution::getTasks(int machine) const {
  return machine_tasks[machine];
}

int Solution::getTotalTCT() const {
  int total_tct = 0;
  for (int m = 0; m < getMachineAmount(); m++) {
    total_tct += getMachineTCT(machine_tasks[m], original_problem->getChangeCosts());
  }
  return total_tct;
}

void Solution::operator=(const Solution& other) {
  original_problem = other.original_problem;
  machine_tasks = new std::vector<int>[original_problem->getMachineAmount()];
  for (int m = 0; m < original_problem->getMachineAmount(); m++) {
    machine_tasks[m] = other.machine_tasks[m];
  }
}
