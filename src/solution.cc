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

#include <algorithm>
#include <cstdio>
#include <stdexcept>
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
  machine_tcts = new int[problem->getMachineAmount()]();
  for (int i = 0; i < problem->getMachineAmount(); i++) {
    machine_tasks[i].reserve(problem->getTaskAmount());
  }
  original_problem = problem;
}

int Solution::testAddTaskIncrement(int machine_index, int task, int position) const {
  const std::vector<int>& machine = machine_tasks[machine_index];
  int const * const * const change_costs = original_problem->getChangeCosts();

  if (machine.size() == 0) {
    return change_costs[0][task];
  }

  int new_tct = 0;
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
  machine_tcts[machine_index] += testAddTaskIncrement(machine_index, task, position);
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

int Solution::testMovement(TaskMovement* movement) const {
  int increment_from = 0;
  int increment_to = 0;
  int const *const *const change_costs = original_problem->getChangeCosts();
  const std::vector<int>& from_machine = machine_tasks[movement->from_machine];
  const std::vector<int>& to_machine = machine_tasks[movement->to_machine];


  if (movement->from_machine == movement->to_machine && movement->to_position == movement->from_position) {
    return 0;
  } else if (movement->from_position == machine_tasks[movement->from_machine].size()) {
    throw std::runtime_error("Task out of machine size");
  } else if (movement->swap && movement->to_position == machine_tasks[movement->to_machine].size()) {
    throw std::runtime_error("Task out of machine size in swap");
  }

  if (movement->swap) {
    // Task swap
    const int* from_task = &(from_machine[movement->from_position]);
    const int* to_task = &(to_machine[movement->to_position]);

    int from_previous = movement->from_position == 0 ? 0 : *(from_task - 1);
    int from_next = movement->from_position == from_machine.size() - 1 ? -1 : *(from_task + 1);

    increment_from -= change_costs[from_previous][*(from_task)] * (from_machine.size() - movement->from_position);
    increment_from += change_costs[from_previous][*(to_task)] * (from_machine.size() - movement->from_position);
    if (from_next != -1) {
      increment_from -= change_costs[*(from_task)][from_next] * (from_machine.size() - movement->from_position - 1);
      increment_from += change_costs[*(to_task)][from_next] * (from_machine.size() - movement->from_position - 1);
    }

    int to_previous = movement->to_position == 0 ? 0 : *(to_task - 1);
    int to_next = movement->to_position == to_machine.size() - 1 ? -1 : *(to_task + 1);

    increment_to -= change_costs[to_previous][*(to_task)] * (to_machine.size() - movement->to_position);
    increment_to += change_costs[to_previous][*(from_task)] * (to_machine.size() - movement->to_position);
    if (to_next != -1) {
      increment_to -= change_costs[*(to_task)][to_next] * (to_machine.size() - movement->to_position - 1);
      increment_to += change_costs[*(from_task)][to_next] * (to_machine.size() - movement->to_position - 1);
    }
  } else {
    if (movement->from_machine != movement->to_machine) {
      const int* from_task = &(from_machine[movement->from_position]);
      const int* to_task = &(to_machine[movement->to_position]);

      int from_previous = movement->from_position == 0 ? 0 : *(from_task - 1);
      if (movement->from_position != from_machine.size() - 1) {
        increment_from -= change_costs[*from_task][*(from_task + 1)] * (from_machine.size() - movement->from_position - 1);
        increment_from += change_costs[from_previous][*(from_task + 1)] * (from_machine.size() - movement->from_position - 1);
      }
      for (int pos = movement->from_position; pos > 0; pos--) {
        increment_from -= change_costs[from_machine[pos - 1]][from_machine[pos]];
      }
      increment_from -= change_costs[0][from_machine[0]];

      int to_previous = movement->to_position == 0 ? 0 : *(to_task - 1);
      if (movement->to_position != to_machine.size() - 1) {
        increment_to -= change_costs[to_previous][*to_task] * (to_machine.size() - movement->to_position);
        increment_to += change_costs[from_previous][*(from_task + 1)] * (from_machine.size() - movement->from_position - 1);
      }
      for (int pos = movement->from_position - 1; pos > 0; pos--) {
        increment_from -= change_costs[from_machine[pos - 1]][from_machine[pos]];
      }
      increment_from -= change_costs[0][from_machine[0]];
    }
  }

  movement->increment_from = increment_from;
  movement->increment_to = increment_to;
  return increment_from + increment_to;
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
