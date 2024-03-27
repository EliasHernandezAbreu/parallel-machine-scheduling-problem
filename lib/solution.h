/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Solution for a PMSP problem
 */

#pragma once

#include <vector>

#include "problem.h"

class Solution {
public:
  /**
   * Constructor for solution class
   * @param problem The problem this solution is for
   */
  Solution(const Problem &problem);

  /**
   * Default destructor for solution
   */
  ~Solution() { delete[] machine_tasks; }

private:
  std::vector<int> *machine_tasks;
};
