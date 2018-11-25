/*
 *
 * What's new in C++
 * Type deduction - auto return type
 * How similar it is to templates
 * (c) Lisher
 *
 */

#include "Logger.h"

int main()
{
  Logger logger;

  std::cout << "Inputs: " << logger.noOfInputs() << std::endl;

  logger.log(11.1f);

  return 0;
}

