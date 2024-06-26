/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents a problem
 */

#include <string>

#include "../lib/problem.h"

Problem::Problem(const std::string &file_name) {
  int *task_setup_cost;
  std::ifstream in(file_name);
  std::string token = "";
  in >> token; // n:
  in >> token; // programs
  task_amount = std::stoi(token);
  in >> token; // m:
  in >> token; // machines
  machine_amount = std::stoi(token);
  in >> token; // Pi:U[1-99] Which is the cost or something
  task_setup_cost = new int[task_amount + 1];
  task_setup_cost[0] = 0; // Pseudo task for position 0 with no cost
  for (int i = 1; i <= task_amount; i++) {
    in >> token; // individual cost
    task_setup_cost[i] = std::stoi(token);
  }
  in >> token; // Sij: U[1-49] yet another something
  // Initialize the change cost array
  task_change_cost = new int *[task_amount + 1];
  for (int i = 0; i <= task_amount; i++) {
    task_change_cost[i] = new int[task_amount + 1];
  }
  // Set change array values
  for (int i = 0; i <= task_amount; i++) {
    for (int j = 0; j <= task_amount; j++) {
      in >> token;
      task_change_cost[i][j] = std::stoi(token) + task_setup_cost[j];
    }
  }
}

int Problem::getChangeCost(int from, int to) const {
  return task_change_cost[from][to];
}

int const *const *const Problem::getChangeCosts() const {
  return task_change_cost;
}

int Problem::getMachineAmount() const { return machine_amount; }

int Problem::getTaskAmount() const { return task_amount; }
