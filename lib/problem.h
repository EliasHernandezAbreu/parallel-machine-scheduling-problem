/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents a PMSP problem
 */

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
   * Gets the startup costs
   * @returns The startup costs
   */
  int const *const getStartupCosts() const { return task_setup_cost; }

  /**
   * Gets the change costs
   * @returns The change costs
   */
  int const *const *const getChangeCosts() const { return task_change_cost; }

private:
  int task_amount;
  int machine_amount;

  int *task_setup_cost;
  int **task_change_cost;
};
