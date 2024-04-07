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
   * Gets the increment on the tct if a task was removed
   * @param position The task to remove
   * @returns The increment
   */
  int testRemoveTask(int position) const;

  int testChangeTask(int position, int task) const;

  int testSwapTasks(int from, int to) const;
  
  int testMoveTask(int from, int to) const;

  /**
   * Adds a task to the machine
   * @param task The task to add
   * @param position The position to add it at
   * @param increment The amount to increment the tct
   */
  void addTask(int task, int position, int increment);

  void removeTask(int position, int increment);

  void changeTask(int position, int task, int increment);

  void swapTasks(int from, int to, int increment);

  void moveTask(int from, int to, int increment);
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
   * Gets the work of a given task
   * @param position The position of the task
   * @param task The task at the position (empty for auto)
   * @param previous_task The task previous to the position (empty for auto)
   * @returns The work of a given task
   */
  int getTaskWork(int position, int task = -1, int previous_task = -1) const;

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
