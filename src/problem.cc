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
  std::ifstream in(file_name);
  std::string token = "";
  in >> token; // n:
  in >> token; // programs
  program_amount = std::stoi(token);
  in >> token; // m:
  in >> token; // machines
  machine_amount = std::stoi(token);
  in >> token; // Pi:U[1-99] Which is the cost or something
  program_startup_cost = new int[program_amount];
  for (int i = 0; i < program_amount; i++) {
    in >> token; // individual cost
    program_startup_cost[i] = std::stoi(token);
  }
  in >> token; // Sij: U[1-49] yet another something
  // Initialize the change cost array
  program_change_cost = new int *[program_amount + 1];
  for (int i = 0; i <= program_amount; i++) {
    program_change_cost[i] = new int[program_amount + 1];
  }
  // Set change array values
  for (int i = 0; i <= program_amount; i++) {
    for (int j = 0; j <= program_amount; j++) {
      in >> token;
      program_change_cost[i][j] = std::stoi(token);
    }
  }
}
