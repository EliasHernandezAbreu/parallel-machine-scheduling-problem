/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents the vns pmsp algorithm
 */

#pragma once

#include "grasp.h"

class Vns : public Grasp {
public:
  /**
   * @constructor
   * @param best_solution_size The amount of best solutions the
   *        algorithm will save to chose randomly from
   * @param repetitions The amount of times the time will repeat
   * @param max_length The maximum amount of movements to do in a perturbation
   */
  Vns(int best_solution_size, int repetitions, int max_length):
    Grasp(best_solution_size, repetitions),
    max_length(max_length) {}

  /**
   * Solves a PMSP problem
   * @param probelm The PMSP probelm
   * @returns The found solution to the problem
   */
  Solution solve(const Problem *problem) const override;

protected:
  int max_length;
};


