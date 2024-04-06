/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Defines the movement of a task in a solution
 */

struct TaskMovement {
  int from_machine;
  int from_task;
  int to_machine;
  int to_task;
  bool swap;
};
