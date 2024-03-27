/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents a PMSP problem
 */

#pragma once

#include <fstream>
#include <string>

class Problem {
public:
  /**
   * Builds a problem from a file specified by its path
   * @param file_name Name of the file to read the problem from
   */
  Problem(const std::string &file_name);

  /**
   * Gets the setup costs
   * @param task The task to get the cost from
   * @returns The startup costs
   */
  int getSetupCost(int task) const;

  /**
   * Gets the change costs from a task to another
   * @param from The task to change from
   * @param to The task to change to
   * @returns The change costs
   */
  int getChangeCosts(int from, int to) const;

  /**
  * Gets the amount of machines in the problem
  * @returns The amount of machines in the problem
  */
  int getMachineAmount() const;

  /**
  * Gets the amount of tasks in the problem
  * @returns The amount of tasks in the problem
  */
  int getTaskAmount() const;

private:
  int task_amount;
  int machine_amount;

  int *task_setup_cost;
  int **task_change_cost;
};
