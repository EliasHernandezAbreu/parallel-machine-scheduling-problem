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

Solution::Solution(const Problem *problem) {
  machine_amount = problem->getMachineAmount();
  machines = new Machine[machine_amount]();
  for (int m = 0; m < machine_amount; m++) {
    machines[m].fromProblem(problem);
  }
}

Solution::Solution() {
  machine_amount = 0;
  machines = nullptr;
}

void Solution::fromProblem(const Problem *problem) {
  machine_amount = problem->getMachineAmount();
  machines = new Machine[machine_amount]();
  for (int m = 0; m < machine_amount; m++) {
    machines[m].fromProblem(problem);
  }
}

void Solution::printMachine(int machine_index) const {
  machines[machine_index].print();
}

void Solution::print() const {
  for (int m = 0; m < machine_amount; m++) {
    printf("%d: %d tasks, tct = %d, confirmed = %d, tasks:\n",
           m,
           machines[m].getSize(),
           machines[m].getTCT(),
           machines[m].confirmTCT());
    machines[m].print();
    printf("\n");
  }
  printf("total TCT = %d, confirmed = %d\n", getTotalTCT(), getConfirmedTotalTCT());
}

void Solution::addTask(int machine_index, int task, int position, int increment) {
  machines[machine_index].addTask(task, position, increment);
}

int Solution::getMachineTCT(int machine_index) const {
  return machines[machine_index].getTCT();
}

int Solution::getTotalTCT() const {
  int total_tct = 0;
  for (int m = 0; m < getMachineAmount(); m++) {
    total_tct += machines[m].getTCT();
  }
  return total_tct;
}


int Solution::getConfirmedTotalTCT() const {
  int total_tct = 0;
  for (int m = 0; m < getMachineAmount(); m++) {
    total_tct += machines[m].confirmTCT();
  }
  return total_tct;
}

int Solution::bestInsert(int task, int* machine_index, int* position) const {
  int best_machine = 0;
  int best_position = 0;
  int best_increment = 99999999;
  for (int m = 0; m < machine_amount; m++) {
    int current_increment;
    int current_position = machines[m].bestInsert(task, &current_increment);
    if (current_increment < best_increment) {
      best_increment = current_increment;
      best_machine = m;
      best_position = current_position;
    }
  }
  machine_index[0] = best_machine;
  position[0] = best_position;
  return best_increment;
}

int Solution::testMovement(TaskMovement* movement) const {
  /*
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
  */
  return 0;
}
