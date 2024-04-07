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
#include <cstdio>

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
  if (size == 0)
    return change_costs[0][task];
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

int Machine::testRemoveTask(int position) const {
  int increment = 0;
  increment -= getTaskWork(position);
  increment -= getTaskWork(position + 1);
  increment += getTaskWork(position + 1, tasks[position + 1], position == 0 ? 0 : tasks[position - 1]);
  for (int i = position - 1; i > 0; i--) {
    increment -= change_costs[tasks[i - 1]][tasks[i]]; 
  }
  if (position != 0)
    increment -= change_costs[0][tasks[0]];
  return increment;
}

int Machine::testChangeTask(int position, int task) const {
  int increment = 0;
  increment -= getTaskWork(position);
  increment -= getTaskWork(position + 1);
  increment += getTaskWork(position, task);
  increment += getTaskWork(position + 1, -1, task);
  return increment;
}

int Machine::testSwapTasks(int from, int to) const {
  int increment = 0;
  if (from == to)
    return 0;
  if (from == to + 1) {
    increment -= getTaskWork(from);
    increment -= getTaskWork(from + 1);
    increment -= getTaskWork(to);
    increment += getTaskWork(from, tasks[to], tasks[from]);
    increment += getTaskWork(from + 1, -1, tasks[to]);
    increment += getTaskWork(to, tasks[from]);
  } else if (to == from + 1) {
    increment -= getTaskWork(from);
    increment -= getTaskWork(to);
    increment -= getTaskWork(to + 1);
    increment += getTaskWork(from, tasks[to]);
    increment += getTaskWork(to, tasks[from], tasks[to]);
    increment += getTaskWork(to + 1, -1, tasks[from]);
  } else {
    increment -= getTaskWork(from);
    increment -= getTaskWork(from + 1);
    increment -= getTaskWork(to);
    increment -= getTaskWork(to + 1);
    increment += getTaskWork(from, tasks[to]);
    increment += getTaskWork(from + 1, -1, tasks[to]);
    increment += getTaskWork(to, tasks[from]);
    increment += getTaskWork(to + 1, -1, tasks[from]);
  }
  return increment;
}

int Machine::testMoveTask(int from, int to) const {
  int increment = 0;
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

void Machine::removeTask(int position, int increment) {
  size--;
  for (int t = position; t < size; t++) {
    tasks[t] = tasks[t + 1];
  }
  tasks[size] = 0;
  tct += increment;
}

void Machine::changeTask(int position, int task, int increment) {
  tasks[position] = task;
  tct += increment;
}

void Machine::swapTasks(int from, int to, int increment) {
  int temp = tasks[from];
  tasks[from] = tasks[to];
  tasks[to] = temp;
  tct += increment;
}

void Machine::moveTask(int from, int to, int increment) {
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

int Machine::getTaskWork(int position, int task, int previous_task) const {
  if (previous_task == -1)
    previous_task = position == 0 ? 0 : tasks[position - 1];
  if (task == -1) {
    if (position >= size)
      return 0;
    task = tasks[position];
  }
  return change_costs[previous_task][task] * (size - position);
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
