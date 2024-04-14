/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Solution for a PMSP problem
 */

#include <cstdio>
#include <cstdlib>

#include "../lib/solution.h"

Solution::Solution(const Problem *problem) {
  machine_amount = problem->getMachineAmount();
  machines = new Machine[machine_amount]();
  for (int m = 0; m < machine_amount; m++) {
    machines[m].fromProblem(problem);
  }
}

Solution::Solution() {
  machine_amount = 0;
  machines = new Machine[1]();
}

Solution::Solution(const Solution& other) {
  machine_amount = other.machine_amount;
  machines = new Machine[machine_amount]();
  for (int m = 0; m < machine_amount; m++) {
    machines[m].copy(other.machines[m]);
  }
}

void Solution::operator=(const Solution& other) {
  machine_amount = other.machine_amount;
  delete[] machines;
  machines = new Machine[machine_amount]();
  for (int m = 0; m < machine_amount; m++) {
    machines[m].copy(other.machines[m]);
  }
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

void Solution::bestInsert(int task, int* increment, int* machine_index, int* position, int result_size) const {
  int worst_best_index = 0;
  int worst_best_increment = 9999999;
  for (int i = 0; i < result_size; i++) {
    machine_index[i] = 0;
    position[i] = 0;
    increment[i] = 9999999;
  }
  for (int m = 0; m < machine_amount; m++) {
    for (int current_position = 0; current_position <= machines[m].getSize(); current_position++) {
      int current_increment = machines[m].testAddTask(task, current_position);
      if (current_increment < worst_best_increment) {
        increment[worst_best_index] = current_increment;
        machine_index[worst_best_index] = m;
        position[worst_best_index] = current_position;
        worst_best_increment = current_increment;
        for (int i = 0; i < result_size; i++) {
          if (increment[i] > worst_best_increment) {
            worst_best_increment = increment[i];
            worst_best_index = i;
          }
        }
      }
    }
  }
}

int Solution::testMovement(TaskMovement* movement) const {
  if (movement->swap) {
    if (movement->from_machine == movement->to_machine) {
      movement->increment_from = machines[movement->from_machine].testSwapTasks(movement->from_position, movement->to_position);
      movement->increment_to = 0;
    } else {
      int from_task = machines[movement->from_machine][movement->from_position];
      int to_task = machines[movement->to_machine][movement->to_position];
      movement->increment_from = machines[movement->from_machine].testChangeTask(movement->from_position, to_task);
      movement->increment_to = machines[movement->from_machine].testChangeTask(movement->to_position, from_task);
    }
  } else {
    if (movement->from_machine == movement->to_machine) {
      Machine& machine = machines[movement->from_machine];
      movement->increment_from = machine.testRemoveTask(movement->from_position);
      int task = machine[movement->from_position];
      machine.removeTask(movement->from_position, 0);
      movement->increment_to = machine.testAddTask(task, movement->to_position);
      machine.addTask(task, movement->from_position, 0);
    } else {
      int task = machines[movement->from_machine][movement->from_position];
      movement->increment_from = machines[movement->from_machine].testRemoveTask(movement->from_position);
      movement->increment_to = machines[movement->to_machine].testAddTask(task, movement->to_position);
    }
  }
  return movement->increment_from + movement->increment_to;
}

void Solution::move(TaskMovement* movement) {
  if (movement->swap) {
    if (movement->from_machine == movement->to_machine) {
      int frompos = movement->from_position;
      int topos = movement->to_position;
      Machine& machine = machines[movement->from_machine];
      machine.swapTasks(frompos, topos, movement->increment_from + movement->increment_to);
    } else {
      Machine& frommach = machines[movement->from_machine];
      Machine& tomach = machines[movement->to_machine];
      int fromtask = frommach[movement->from_position];
      int totask = tomach[movement->to_position];
      frommach.changeTask(movement->from_position, totask, movement->increment_from);
      tomach.changeTask(movement->to_position, fromtask, movement->increment_to);
    }
  } else {
    if (movement->from_machine == movement->to_machine) {
      Machine& machine = machines[movement->from_machine];
      int task = machine[movement->from_position];
      machine.removeTask(movement->from_position, movement->increment_from);
      machine.addTask(task, movement->to_position, movement->increment_to);
    } else {
      Machine& frommach = machines[movement->from_machine];
      Machine& tomach = machines[movement->to_machine];
      int task = frommach[movement->from_position];
      frommach.removeTask(movement->from_position, movement->increment_from);
      tomach.addTask(task, movement->to_position, movement->increment_to);
    }
  }
}

int Solution::sameMachineReinsert() {
  int best_remove_increment = 0;
  int best_insert_increment = 0;
  int best_machine = 0;
  int best_insert_position = 0;
  int best_remove_position = 0;
  for (int m = 0; m < machine_amount; m++) {
    for (int pos = 0; pos < machines[m].getSize(); pos++) {
      int removed_task = machines[m][pos];
      int remove_increment = machines[m].testRemoveTask(pos);
      int insert_increment;
      machines[m].removeTask(pos, remove_increment);
      int insert_position = machines[m].bestInsert(removed_task, &insert_increment);
      machines[m].addTask(removed_task, pos, -remove_increment);
      if (insert_increment + remove_increment < best_insert_increment + best_remove_increment) {
        best_insert_increment = insert_increment;
        best_remove_increment = remove_increment;
        best_machine = m;
        best_insert_position = insert_position;
        best_remove_position = pos;
      }
    }
  }
  if (best_insert_increment + best_remove_increment == 0) {
    return 0;
  }
  int task = machines[best_machine][best_remove_position];
  machines[best_machine].removeTask(best_remove_position, best_remove_increment);
  machines[best_machine].addTask(task, best_insert_position, best_insert_increment);
  return best_insert_increment + best_remove_increment;
}

int Solution::globalReinsert() {
  int best_remove_increment = 0;
  int best_insert_increment = 0;
  int best_remove_machine = 0;
  int best_insert_machine = 0;
  int best_insert_position = 0;
  int best_remove_position = 0;
  for (int m = 0; m < machine_amount; m++) {
    for (int pos = 0; pos < machines[m].getSize(); pos++) {
      int removed_task = machines[m][pos];
      int remove_increment = machines[m].testRemoveTask(pos);
      int insert_increment;
      int insert_position;
      int insert_machine;
      machines[m].removeTask(pos, remove_increment);
      bestInsert(removed_task, &insert_increment, &insert_machine, &insert_position, 0);
      machines[m].addTask(removed_task, pos, -remove_increment);
      if (insert_increment + remove_increment < best_insert_increment + best_remove_increment) {
        best_insert_increment = insert_increment;
        best_remove_increment = remove_increment;
        best_insert_machine = insert_machine;
        best_remove_machine = m;
        best_insert_position = insert_position;
        best_remove_position = pos;
      }
    }
  }
  if (best_insert_increment + best_remove_increment == 0) {
    return 0;
  }
  int task = machines[best_remove_machine][best_remove_position];
  machines[best_remove_machine].removeTask(best_remove_position, best_remove_increment);
  machines[best_insert_machine].addTask(task, best_insert_position, best_insert_increment);
  return best_insert_increment + best_remove_increment;
}

int Solution::sameMachineSwap() {
  int best_machine = 0;
  int best_from_position = 0;
  int best_to_position = 0;
  int best_increment = 0;
  for (int m = 0; m < machine_amount; m++) {
    for (int from_p = 0; from_p < machines[m].getSize(); from_p++) {
      for (int to_p = 0; to_p < machines[m].getSize(); to_p++) {
        int inc = machines[m].testSwapTasks(from_p, to_p);
        if (inc < best_increment) {
          best_machine = m;
          best_from_position = from_p;
          best_to_position = to_p;
          best_increment = inc;
        }
      }
    }
  } 
  if (best_increment == 0) return 0;
  machines[best_machine].swapTasks(best_from_position, best_to_position, best_increment);
  return best_increment;
}

int Solution::globalSwap() {
  int best_machine_from = 0;
  int best_machine_to = 0;
  int best_from_position = 0;
  int best_to_position = 0;
  int best_to_increment = 0;
  int best_from_increment = 0;
  for (int from_m = 0; from_m < machine_amount; from_m++) {
    for (int to_m = 0; to_m < machine_amount; to_m++) {
      for (int from_p = 0; from_p < machines[from_m].getSize(); from_p++) {
        for (int to_p = 0; to_p < machines[to_m].getSize(); to_p++) {
          int from_inc = 0;
          int to_inc = 0;
          if (from_m == to_m) {
            from_inc = machines[from_m].testSwapTasks(from_p, to_p);
            to_inc = 0;
          } else {
            from_inc += machines[from_m].testChangeTask(from_p, machines[to_m][to_p]);
            to_inc += machines[to_m].testChangeTask(to_p, machines[from_m][from_p]);
          }
          if (from_inc + to_inc < best_to_increment + best_from_increment) {
            best_machine_from = from_m;
            best_machine_to = to_m;
            best_from_position = from_p;
            best_to_position = to_p;
            best_to_increment = to_inc;
            best_from_increment = from_inc;
          }
        }
      }
    } 
  } 
  if (best_from_increment + best_to_increment >= 0) return 0;
  if (best_machine_from == best_machine_to) {
    machines[best_machine_from].swapTasks(best_from_position, best_to_position, best_from_increment + best_to_increment);
  } else {
    int from_task = machines[best_machine_from][best_from_position];
    int to_task = machines[best_machine_to][best_to_position];
    machines[best_machine_from].changeTask(best_from_position, to_task, best_from_increment);
    machines[best_machine_to].changeTask(best_to_position, from_task, best_to_increment);
  }
  return best_to_increment + best_from_increment;
}

void Solution::vnd() {
  int current_increment = -1;
  while (current_increment < 0) {
    current_increment = globalReinsert();
    if (current_increment < 0) continue;
    current_increment = sameMachineSwap();
    if (current_increment < 0) continue;
    current_increment = sameMachineReinsert();
    if (current_increment < 0) continue;
    current_increment = globalSwap();
    if (current_increment < 0) continue;
    break;
  }
}

void Solution::perturbate(int length) {
  for (int i = 0; i < length; i++) {
    TaskMovement movement;
    movement.from_machine = rand() % machine_amount;
    movement.to_machine = rand() % machine_amount;
    movement.from_position = rand() % machines[movement.from_machine].getSize();
    movement.to_position = rand() % machines[movement.to_machine].getSize();
    movement.swap = rand() % 1;
    testMovement(&movement);
    move(&movement);
  }
}
