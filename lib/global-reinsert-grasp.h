/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents the grasp PMSP algorithm with global reinsert improvement
 */

#pragma once

#include "algorithm.h"
#include "grasp.h"
#include "solution.h"

class GlobalReinsertGrasp : public Grasp {
public:
  /**
   * @constructor
   * @param best_solution_size The amount of best solutions the
   *        algorithm will save to chose randomly from
   */
  GlobalReinsertGrasp(int best_solution_size, int repetitions);

  /**
   * Improves the obtained solution
   * @param solution A pointer to the solution to improve
   * @returns The increment of the improvement
   */
  int improveSolution(Solution* solution) const override;
};



