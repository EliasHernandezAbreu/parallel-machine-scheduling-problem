/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Defines the movement of a task in a solution
 */

#pragma once

struct TaskMovement {
  int from_machine;
  int from_position;
  int to_machine;
  int to_position;
  bool swap;
  int increment_from;
  int increment_to;
};
