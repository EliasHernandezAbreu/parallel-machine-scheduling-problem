/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 */

#include <cstdio>
#include <string>

#include "../lib/greedy.h"
#include "../lib/grasp.h"
#include "../lib/problem.h"

int main(int argc, char** argv) {
  srand(time(NULL));

  if (argc < 2) {
    printf("Add the file to solve as an argument\n");
    return 1;
  }

  int chosen_solver;
  printf("[0] Greedy\n[1] Grasp\nChoose the solver to use: ");
  scanf("%d", &chosen_solver);
  Algorithm *solver;
  if (chosen_solver == 0) {
    solver = new Greedy();
  } else if (chosen_solver == 1) {
    solver = new Grasp(2, 100);
  } else {
    printf("Please use a valid input. Input given: %d\n", chosen_solver);
    return 1;
  }

  Problem problem(argv[1]);
  Solution solution = solver->solve(&problem);
  printf("\n");
  solution.print();

  delete solver;
  return 0;
}
