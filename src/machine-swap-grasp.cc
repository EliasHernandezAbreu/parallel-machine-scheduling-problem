/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents the grasp PMSP algorithm with same machine swap improvement
 */

#include "../lib/machine-swap-grasp.h"

MachineSwapGrasp::MachineSwapGrasp(int best_solution_size, int repetitions):
  Grasp(best_solution_size, repetitions) {
}

int MachineSwapGrasp::improveSolution(Solution* solution) const {
  return solution->sameMachineSwap();
}

