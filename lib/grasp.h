/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents the grasp PMSP algorithm
 */

#pragma once

#include "algorithm.h"
#include "solution.h"

class Grasp : public Algorithm {
public:
  /**
   * @constructor
   * @param best_solution_size The amount of best solutions the
   *        algorithm will save to chose randomly from
   */
  Grasp(int best_solution_size, int repetitions);

  /**
   * Solves the constructive phase
   * @param problem The problem to solve from
   * @returns The solution
   */
  Solution constructivePhase(const Problem* problem) const;

  /**
   * Improves the obtained solution
   * @param solution A pointer to the solution to improve
   * @returns The increment of the improvement
   */
  virtual int improveSolution(Solution* solution) const;

  /**
   * Solves a PMSP problem
   * @param probelm The PMSP probelm
   * @returns The found solution to the problem
   */
  virtual Solution solve(const Problem *problem) const override;

protected:
  int best_solutions_size;
  int repetitions;
};

