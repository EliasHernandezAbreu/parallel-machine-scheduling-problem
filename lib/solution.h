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
#include <vector>

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
   * Changes the problem used by the solution
   * @param problem The new problem
  */
  void ChangeProblem(const Problem*);

  /**
   * Default destructor for solution
   */
  ~Solution() { delete[] machine_tasks; }

  /**
   * Gets the tasks assosiated to a machine
   * @param machine The machine to get the tasks from
   * @returns The tasks assosiated to that machine
   */
  const std::vector<int> &getTasks(int machine) const;

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
  */
  void addTask(int machine, int task, int position);

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
   * Gets the TCT of this machine
   * @returns The TCT of this machine
   */
  int getConfirmedSlowMachineTCT(int machine_index) const;

  /**
  * Gets the total TCT of this solution
  * @returns The total tct of the solution
  */
  int getConfirmedSlowTotalTCT() const;

  /**
   * Returns the current machine as a string
   * @returns A string that represents the machine
   */
  void printMachine(int machine_index) const;

  /**
  * Gets the amount of machines
  * @returns The amount of machines
  */
  int getMachineAmount() const { return original_problem->getMachineAmount(); }

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
   * Copies a solution
   * @param other The other solution
  */
  void operator=(const Solution& other);

private:
  const Problem* original_problem;
  int* machine_tcts;
  std::vector<int> *machine_tasks;
};
