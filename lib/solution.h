/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Solution for a PMSP problem
 */

#pragma once

#include <string>

#include "machine.h"
#include "problem.h"
#include "task-movement.h"

class Solution {
public:
  /**
   * Constructor for solution class
   * @param problem The problem this solution is for
   */
  Solution(const Problem*);

  /**
   * Default constructor
  */
  Solution();

  /**
   * Copy constructor
   * @param solution The solution to copy
   */
  Solution(const Solution& solution);

  /**
   * Changes the problem used by the solution
   * @param problem The new problem
  */
  void fromProblem(const Problem*);

  /**
   * Default destructor for solution
   */
  ~Solution() { delete[] machines; }

  /**
  * Tests the resulting TCT of a machine
  * @param machine The machine to test
  * @param task The task to add
  * @param position The position to add it in
  * @returns The total TCT of the machin after doing it
  */
  int testAddTaskIncrement(int machine, int task, int position) const;

  /**
  * Adds a task to a machine in a position
  * @param machine The machine to test
  * @param task The task to add
  * @param position The position to add it in
  * @param increment The increment of said insertion
  */
  void addTask(int machine, int task, int position, int increment);

  /**
   * Gets the best machine and position to insert a task
   * @param task The task to insert
   * @param increment The best increments found
   * @param machine_index The best machine to put it in
   * @param position The best position to place it at
   * @param result_size The amount of results to keep
   * @returns The increment of said insertion
   */
  void bestInsert(int task, int* increment, int* machine_index, int* position, int result_size) const;

  /**
   * Gets the TCT of this machine
   * @returns The TCT of this machine
   */
  int getMachineTCT(int machine_index) const;

  /**
  * Gets the total TCT of this solution
  * @returns The total tct of the solution
  */
  int getTotalTCT() const;

  /**
  * Gets the total TCT of this solution
  * @returns The total tct of the solution
  */
  int getConfirmedTotalTCT() const;

  /**
   * Returns the current machine as a string
   * @returns A string that represents the machine
   */
  void printMachine(int machine_index) const;

  /**
   * Prints the solution
   */
  void print() const;

  /**
  * Gets the amount of machines
  * @returns The amount of machines
  */
  int getMachineAmount() const { return machine_amount; }

  /**
   * Tests the movement of a task.
   * If the destination machine is <0, it will do a global reinsertion.
   * If the destination machine is not <0 but the destination task is, it will do a
   * reinsertion in the same machine.
   * Sets the increment_from and increment_to to the machines the task was removed from,
   * and the one it was added to. If those are the same machine, the resulting increment
   * of the machine will be the sum of both.
   * @param movement The movement to test
   * @returns The resulting total increment of the movement
   */
  int testMovement(TaskMovement* movement) const;

  /**
   * Improves the solution by reinserting a task in its same machine
   * @returns The improvement
   */
  int sameMachineReinsert();

  /**
   * Improves the solution by reinserting a task globally
   * @returns The improvement
   */
  int globalReinsert();

  /**
   * Improves the solution by swapping two tasks in the same machine
   * @returns The improvement
   */
  int sameMachineSwap();

  /**
   * Improves the solution by swapping two tasks globally
   * @returns The improvement
   */
  int globalSwap();

  /**
   * Copies a solution
   * @param other The other solution
  */
  void operator=(const Solution& other);

  /**
  * Runs the vnd algorithm from the current solution
  */
  void vnd();

private:
  int machine_amount;
  Machine* machines;
};
