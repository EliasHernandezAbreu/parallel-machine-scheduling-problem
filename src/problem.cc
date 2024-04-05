/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents a problem
 */

#include <cstdio>
#include <string>

#include "../lib/problem.h"

Problem::Problem(const std::string &file_name) {
  FILE* input = fopen(file_name.c_str(), "r");
  if (input != nullptr) {
    char trash[15]; // String for storing non useful input data
    fscanf(input, "n: %d\nm: %d\n", &task_amount, &machine_amount);
    int task_setup_cost[task_amount + 1];
    task_setup_cost[0] = 0;
    fscanf(input, "%s", trash); // string that indicates start of task setup costs
    for (int i = 0; i < task_amount; i++) {
      int current_task_cost;
      fscanf(input, "%d", &current_task_cost);
      task_setup_cost[i + 1] = current_task_cost;
    }
    fscanf(input, "%s", trash); // string that indicates start of change costs
    task_change_cost = new int*[task_amount + 1];
    for (int i = 0; i <= task_amount; i++) {
      task_change_cost[i] = new int[task_amount + 1];
    }
    for (int i = 0; i <= task_amount; i++) {
      for (int j = 0; j <= task_amount; j++) {
        fscanf(input, "%d", &task_change_cost[i][j]);
        task_change_cost[i][j] += task_setup_cost[j];
      }
    }
  }
  fclose(input);
}

int Problem::getChangeCost(int from, int to) const {
  return task_change_cost[from][to];
}

int const *const *const Problem::getChangeCosts() const {
  return task_change_cost;
}

int Problem::getMachineAmount() const { return machine_amount; }

int Problem::getTaskAmount() const { return task_amount; }
