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

#include <cstdio>
#include <vector>

Solution::Solution(const Problem *problem) {
  machine_tcts = new int[problem->getMachineAmount()]();
  machine_tasks = new std::vector<int>[problem->getMachineAmount()];
  for (int i = 0; i < problem->getMachineAmount(); i++) {
    machine_tasks[i].reserve(problem->getTaskAmount());
  }
  original_problem = problem;
}
Solution::Solution() {
  machine_tasks = nullptr;
  machine_tcts = nullptr;
  original_problem = nullptr;
}

void Solution::ChangeProblem(const Problem *problem) {
  if (machine_tasks != nullptr)
    delete[] machine_tasks;
  if (machine_tcts != nullptr)
    delete[] machine_tcts;
  machine_tasks = new std::vector<int>[problem->getMachineAmount()];
  machine_tcts = new int[problem->getMachineAmount()];
  for (int i = 0; i < problem->getMachineAmount(); i++) {
    machine_tasks[i].reserve(problem->getTaskAmount());
  }
  original_problem = problem;
}

int Solution::testAddTaskTCT(int machine_index, int task, int position) const {
  const std::vector<int>& machine = machine_tasks[machine_index];
  int const * const * const change_costs = original_problem->getChangeCosts();

  if (machine.size() == 0) {
    return change_costs[0][task];
  }

  int new_tct = machine_tcts[machine_index];
  if (position == 0) {
    new_tct -= change_costs[0][machine[0]] * machine.size();
    new_tct += change_costs[task][machine[0]] * machine.size();
    new_tct += change_costs[0][task] * (machine.size() + 1);
    return new_tct;
  }
  
  if (position == machine.size()) {
    new_tct += change_costs[machine[position - 1]][task];

  } else {
    new_tct -= change_costs[machine[position - 1]][machine[position]] * (machine.size() - position);
    new_tct += change_costs[machine[position - 1]][task] * (machine.size() - position + 1);
    new_tct += change_costs[task][machine[position]] * (machine.size() - position);
  }
  
  for (int i = position - 1; i > 0; i--) {
    new_tct += change_costs[machine[i - 1]][machine[i]]; 
  }
  new_tct += change_costs[0][machine[0]];
  return new_tct;
}

void Solution::printMachine(int machine_index) const {
  const std::vector<int>& machine = machine_tasks[machine_index];
  printf("[");
  for (int i = 0; i < machine.size(); i++) {
    if (i == 0) {
      printf("%d", machine[0]);
    } else {
      printf(" -> %d", machine[i]);
    }
  }
  printf("]");
}

void Solution::addTask(int machine_index, int task, int position) {
  machine_tcts[machine_index] = testAddTaskTCT(machine_index, task, position);
  std::vector<int>& machine = machine_tasks[machine_index];
  machine.emplace(machine.begin() + position, task);
}

const std::vector<int> &Solution::getTasks(int machine) const {
  return machine_tasks[machine];
}

int Solution::getMachineTCT(int machine_index) const {
  return machine_tcts[machine_index];
}

int Solution::getTotalTCT() const {
  int total_tct = 0;
  for (int m = 0; m < getMachineAmount(); m++) {
    total_tct += machine_tcts[m];
  }
  return total_tct;
}

int Solution::getConfirmedSlowMachineTCT(int machine_index) const {
  const std::vector<int>& machine = machine_tasks[machine_index];
  int result = 0;
  for (int i = 0; i < machine.size(); i++) {
    int work = 0;
    if (i == 0) {
      work += original_problem->getChangeCost(0, machine[0]);
      } else {
      work += original_problem->getChangeCost(machine[i - 1], machine[i]);
    }
    work *= machine.size() - i;
    result += work;
  }
  return result;
}

int Solution::getConfirmedSlowTotalTCT() const {
  int total_tct = 0;
  for (int m = 0; m < getMachineAmount(); m++) {
    total_tct += getConfirmedSlowMachineTCT(m);
  }
  return total_tct;
}

void Solution::operator=(const Solution& other) {
  if (machine_tcts != nullptr)
    delete[] machine_tcts;
  if (machine_tasks != nullptr) 
    delete[] machine_tasks;
  original_problem = other.original_problem;
  machine_tasks = new std::vector<int>[original_problem->getMachineAmount()];
  for (int m = 0; m < original_problem->getMachineAmount(); m++) {
    machine_tasks[m] = other.machine_tasks[m];
  }
  machine_tcts = new int[original_problem->getMachineAmount()];
  for (int tct = 0; tct < original_problem->getMachineAmount(); tct++) {
    machine_tcts[tct] = other.getMachineTCT(tct);
  }
}
