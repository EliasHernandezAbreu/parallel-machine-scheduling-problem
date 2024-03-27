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
#include "../lib/problem.h"
#include "../lib/utils.h"

int main() {
  Problem problem("test/i40/I40j_2m_S1_1.txt");
  Algorithm *solver = new GreedyPMSP();
  Solution solution = solver->solve(&problem);

  for (int machine = 0; machine < problem.getMachineAmount(); machine++) {
    printf("machine %d: %s\n", machine, printMachine(solution.getTasks(machine)).c_str());
  }

  delete solver;
  return 0;
}
