/**
 * Diseño y Analisis de algoritmos
 * Practica 7 - PMSP
 *
 * @author Elias Hernandez Abreu <alu0101487137@ull.edu.es>
 * @since 20 mar 2024
 *
 * @file Represents a problem
 */

#include <fstream>
#include <string>

class Problem {
public:
  /**
   * @constructor
   * @argument file_name Name of the file to read the problem from
   */
  Problem(const std::string &file_name);

private:
  int machine_amount;
  int program_amount;

  int *program_startup_cost;
  int **program_change_cost;
};
