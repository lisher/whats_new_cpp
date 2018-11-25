/*
 *
 * What's new in C++
 * Type deduction - auto return type
 * How similar it is to templates
 * (c) Lisher
 *
 */

#include "Logger.h"


/*
 * Uncommenting this will make compilation pass
 * but linker most definitely will not be happy.

auto Logger::noOfOutputs() const
{
  return 8u;
}

auto Logger::logWithDate(float value) const
{
  std::cout << "[Today] Value = " << value << std::endl;

  return value;
}

*/

int main()
{
  Logger logger;

  std::cout << "Inputs: " << logger.noOfInputs() << std::endl;
  std::cout << "Outputs: " << logger.noOfOutputs() << std::endl;

  logger.log(11.1f);
  logger.logWithDate(11.1f);

  return 0;
}

