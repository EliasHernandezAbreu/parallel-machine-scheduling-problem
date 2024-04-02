/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents the greedy PMSP algorithm
 */

#pragma once

#include "algorithm.h"

class GraspPMSP : public Algorithm {
public:
  /**
   * @constructor
   * @param best_solution_size The amount of best solutions the
   *        algorithm will save to chose randomly from
   */
  GraspPMSP(int best_solution_size);

  /**
   * Solves a PMSP problem
   * @param probelm The PMSP probelm
   * @returns The found solution to the problem
   */
  Solution solve(const Problem *problem) const override;

private:
  int best_solutions_size;
};

