/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 */

#define TEST

#include <cstdio>
#include <string>

#include "../lib/greedy.h"
#include "../lib/grasp.h"
#include "../lib/problem.h"

#ifndef TEST
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
    solver = new Grasp(3, 100);
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
#endif

#ifdef TEST
int main(int argc, char** argv) {
  Problem problem(argv[1]);
  Machine test_machine;
  test_machine.fromProblem(&problem);

  test_machine.addTask(1, 0, test_machine.testAddTask(1, 0));
  test_machine.addTask(2, 1, test_machine.testAddTask(2, 1));
  test_machine.addTask(3, 2, test_machine.testAddTask(3, 2));
  test_machine.print();
  printf(" - tct = %d, confirmed = %d\n", test_machine.getTCT(), test_machine.confirmTCT());

  printf("works: 1=%d, 2=%d, 3=%d\n", 
         test_machine.getTaskWork(0),
         test_machine.getTaskWork(1),
         test_machine.getTaskWork(2));

  test_machine.removeTask(2, test_machine.testRemoveTask(2));
  test_machine.print();
  printf(" - tct = %d, confirmed = %d\n", test_machine.getTCT(), test_machine.confirmTCT());

  test_machine.changeTask(1, 3, test_machine.testChangeTask(1, 3));
  test_machine.print();
  printf(" - tct = %d, confirmed = %d\n", test_machine.getTCT(), test_machine.confirmTCT());
  test_machine.changeTask(0, 2, test_machine.testChangeTask(0, 2));
  test_machine.print();
  printf(" - tct = %d, confirmed = %d\n", test_machine.getTCT(), test_machine.confirmTCT());
  test_machine.addTask(1, 2, test_machine.testAddTask(1, 2));
  test_machine.print();
  printf(" - tct = %d, confirmed = %d\n", test_machine.getTCT(), test_machine.confirmTCT());
  test_machine.swapTasks(0, 2, test_machine.testSwapTasks(0, 2));
  test_machine.print();
  printf(" - tct = %d, confirmed = %d\n", test_machine.getTCT(), test_machine.confirmTCT());
  test_machine.swapTasks(1, 2, test_machine.testSwapTasks(1, 2));
  test_machine.print();
  printf(" - tct = %d, confirmed = %d\n", test_machine.getTCT(), test_machine.confirmTCT());
  test_machine.swapTasks(1, 0, test_machine.testSwapTasks(1, 0));
  test_machine.print();
  printf(" - tct = %d, confirmed = %d\n", test_machine.getTCT(), test_machine.confirmTCT());

  return 0;
}
#endif
