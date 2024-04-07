/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents a machine
 */

#include "../lib/machine.h"

Machine::Machine() {
  change_costs = nullptr;
  tasks = nullptr;
  capacity = 0;
  size = 0;
  tct = 0;
}

Machine::Machine(const Machine& other) {
  change_costs = other.change_costs;
  capacity = other.capacity;
  size = other.size;
  tct = other.tct;
  tasks = new int[capacity];
  for (int t = 0; t < size; t++) {
    tasks[t] = other.tasks[t];
  }
}

void Machine::copy(const Machine& other) {
  change_costs = other.change_costs;
  capacity = other.capacity;
  size = other.size;
  tct = other.tct;
  tasks = new int[capacity];
  for (int t = 0; t < size; t++) {
    tasks[t] = other.tasks[t];
  }
}

void Machine::fromProblem(const Problem* problem) {
  capacity = problem->getTaskAmount();
  size = 0;
  tct = 0;
  tasks = new int[capacity];
  change_costs = problem->getChangeCosts();
}

void Machine::print() const {
  printf("[");
  for (int i = 0; i < size; i++) {
    if (i == 0) {
      printf("%d", tasks[0]);
    } else {
      printf(" -> %d", tasks[i]);
    }
  }
  printf("]");
}

int Machine::testAddTask(int task, int position) const {
  if (size == 0) {
    return change_costs[0][task];
  }

  int increment = 0;
  if (position == 0) {
    increment -= change_costs[0][tasks[0]] * size;
    increment += change_costs[task][tasks[0]] * size;
    increment += change_costs[0][task] * (size + 1);
    return increment;
  }

  if (position == size) {
    increment += change_costs[tasks[position - 1]][task];

  } else {
    increment -= change_costs[tasks[position - 1]][tasks[position]] * (size - position);
    increment += change_costs[tasks[position - 1]][task] * (size - position + 1);
    increment += change_costs[task][tasks[position]] * (size - position);
  }
  
  for (int i = position - 1; i > 0; i--) {
    increment += change_costs[tasks[i - 1]][tasks[i]]; 
  }
  increment += change_costs[0][tasks[0]];
  return increment;
}

void Machine::addTask(int task, int position, int increment) {
  for (int t = size; t > position; t--) {
    tasks[t] = tasks[t - 1];
  }
  size++;
  tct += increment;
  tasks[position] = task;
}

int Machine::bestInsert(int task, int* increment) const {
  int best_increment = 999999;
  int best_position = 0;
  for (int position = 0; position <= size; position++) {
    int current_increment = testAddTask(task, position);
    if (current_increment < best_increment) {
      best_increment = current_increment;
      best_position = position;
    }
  }
  increment[0] = best_increment;
  return best_position;
}

int Machine::getTCT() const {
  return tct;
}

int Machine::confirmTCT() const {
  int result = 0;
  for (int i = 0; i < size; i++) {
    int work = 0;
    if (i == 0) {
      work += change_costs[0][tasks[0]];
      } else {
      work += change_costs[tasks[i - 1]][tasks[i]];
    }
    work *= size - i;
    result += work;
  }
  return result;
}

int Machine::getSize() const {
  return size;
}

int const *const Machine::getTasks() const {
  return tasks;
}
