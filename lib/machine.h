/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents a machine
 */

#pragma once

#include "problem.h"
#include <cstdio>

class Machine {
public:
  /**
  * Default constructor
  */
  Machine();

  /**
   * Copy constructor
   * @param other The machine to copy
   */
  Machine(const Machine& other);

  /**
   * Copies other machine
   * @param Machine to copy
   */
  void copy(const Machine& other);

  /**
   * Default destructor
   */
  ~Machine() {
    delete[] tasks;
  }

  /**
   * Prints the machine to the default output.
   */
  void print() const;

  /**
   * Gets the increment on the tct if a task was added
   * @param task The task to add
   * @param position The position to add it at
   * @returns The resulting increment of the operation
   */
  int testAddTask(int task, int position) const;

  /**
   * Adds a task to the machine
   * @param task The task to add
   * @param position The position to add it at
   * @param increment The amount to increment the tct
   */
  void addTask(int task, int position, int increment);

  /**
   * Gets the best insert and position for a task
   * @param task The task to test
   * @param increment A pointer to the position where to store the increment
   * @returns The best position to store the task
   */
  int bestInsert(int task, int* increment) const;

  /**
  * Initialize from problem
  * @param problem The problem to initialize from
  */
  void fromProblem(const Problem* problem);

  /**
  * Gets the tct of the machine
  * @returns The tct of the machine
  */
  int getTCT() const;

  /**
  * Computes the entire tct of the machine
  * @returns The confirmed tct of the machine
  */
  int confirmTCT() const;

  /**
  * Gets the amount of tasks in the machine
  * @returns The amount of tasks in the machine
  */
  int getSize() const;

  int const *const getTasks() const;

private:
  int** change_costs;
  int* tasks;
  int size;
  int capacity;
  int tct;
};
