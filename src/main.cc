/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 */

#define TEST

#include <cstdio>
#include <ctime>
#include <string>
#include <time.h>

#include "../lib/greedy.h"
#include "../lib/grasp.h"
#include "../lib/vns.h"
#include "../lib/problem.h"

#include "../lib/machine-reinsert-grasp.h"
#include "../lib/machine-swap-grasp.h"
#include "../lib/global-reinsert-grasp.h"
#include "../lib/global-swap-grasp.h"

#ifndef TEST
int main(int argc, char** argv) {
  srand(time(NULL));

  if (argc < 2) {
    printf("Add the file to solve as an argument\n");
    return 1;
  }

  int chosen_solver;
  printf("[0] Greedy\n[1] Grasp\n[2] VNS\nChoose the solver to use: ");
  scanf("%d", &chosen_solver);
  Algorithm *solver;
  if (chosen_solver == 0) {
    solver = new Greedy();
  } else if (chosen_solver == 1) {
    printf("\n[0] None\n[1] Same machine reinsert\n[2] Same machine swap\n");
    printf("[3] Global reinsert\n[4] Global swap\nChoose the improvement algorithm to use: ");
    int chosen_improvement;
    scanf("%d", &chosen_improvement);
    if (chosen_improvement == 0) {
      solver = new Grasp(3, 100);
    } else if (chosen_improvement == 1) {
      solver = new MachineReinsertGrasp(3, 100);
    } else if (chosen_improvement == 2) {
      solver = new MachineSwapGrasp(3, 100);
    }else if (chosen_improvement == 3) {
      solver = new GlobalReinsertGrasp(3, 100);
    }else if (chosen_improvement == 4) {
      solver = new GlobalSwapGrasp(3, 100);
    }else {
      printf("Please use a valid input. Input given: %d\n", chosen_improvement);
      return 1;
    }
  } else if (chosen_solver == 2) {
    solver = new Vns(3, 100, 6);
  } else {
    printf("Please use a valid input. Input given: %d\n", chosen_solver);
    return 1;
  }

  Problem problem(argv[1]);
  long t = clock();
  Solution solution= solver->solve(&problem);
  double time = (double)(clock() - t) / CLOCKS_PER_SEC;
  if (time < 0.1) {
    printf("Time = %f ms\n", time * 1000);
  } else {
    printf("Time = %f s\n", time);
  }
  printf("\n");
  solution.print();

  delete solver;
  return 0;
}
#endif


#ifdef TEST
void testProblems(const int prob_amount, const char** problems, Algorithm* solver) {
  for (int p = 0; p < prob_amount; p++) {
    Problem problem(problems[p]);
    long t = clock();
    Solution solution = solver->solve(&problem);
    double time = (double)(clock() - t) / CLOCKS_PER_SEC;
    printf("Test: %s\n", problems[p]);
    if (time < 0.1) {
      printf("Time = %.3f ms\n", time * 1000);
    } else {
      printf("Time = %.3f s\n", time);
    }
    printf("TCT = %d, (%d)\n", solution.getTotalTCT(), solution.getConfirmedTotalTCT());
  }
}

int main(int argc, char** argv) {
  srand(time(NULL));

  const int problem_amount = 6;
  const char* problems[problem_amount] = {
    "test/i40/I40j_2m_S1_1.txt",
    "test/i40/I40j_4m_S1_1.txt",
    "test/i40/I40j_8m_S1_1.txt",
    "test/i70/I70j_2m_S1_1.txt",
    "test/i70/I70j_4m_S1_1.txt",
    "test/i70/I70j_8m_S1_1.txt"
  };

  Algorithm* solver;
  puts("\nGREEDY");
  solver = new Greedy();
  testProblems(problem_amount, problems, solver);

  puts("\nGRASP");
  delete solver;
  solver = new Grasp(3, 100);
  testProblems(problem_amount, problems, solver);

  puts("\nLOCAL SWAP GRASP");
  delete solver;
  solver = new MachineSwapGrasp(3, 100);
  testProblems(problem_amount, problems, solver);

  puts("\nLOCAL REINSERT GRASP");
  delete solver;
  solver = new MachineReinsertGrasp(3, 100);
  testProblems(problem_amount, problems, solver);

  puts("\nGLOBAL SWAP GRASP");
  delete solver;
  solver = new GlobalSwapGrasp(3, 100);
  testProblems(problem_amount, problems, solver);

  puts("\nGLOBAL REINSERT GRASP");
  delete solver;
  solver = new GlobalReinsertGrasp(3, 100);
  testProblems(problem_amount, problems, solver);
  
  puts("\nVNS");
  delete solver;
  solver = new Vns(3, 100, 5);
  testProblems(problem_amount, problems, solver);
}

#endif
