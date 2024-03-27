/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents a PMSP algorithm
 */

#pragma once

#include "problem.h"
#include "solution.h"

class Algorithm {
public:
  /**
   * Solves a PMSP problem
   * @param probelm The PMSP probelm
   * @returns The found solution to the problem
   */
  virtual Solution solve(const Problem *problem) const = 0;

  virtual ~Algorithm(){};
};
