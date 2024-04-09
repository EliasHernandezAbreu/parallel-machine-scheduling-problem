/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents the grasp PMSP algorithm with global reinsert improvement
 */

#include "../lib/global-reinsert-grasp.h"

GlobalReinsertGrasp::GlobalReinsertGrasp(int best_solution_size, int repetitions):
  Grasp(best_solution_size, repetitions) {
}

int GlobalReinsertGrasp::improveSolution(Solution* solution) const {
  return solution->globalReinsert();
}


