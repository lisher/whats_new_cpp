/*
 *
 * What's new in C++
 * Type deduction - auto return type
 * (c) Lisher
 *
 */

#include "Logger.h"


auto Logger::noOfOutputs() const
{
  return 8u;
}

auto Logger::logWithDate(float value) const
{
  std::cout << "[Today] Value = " << value << std::endl;

  return value;
}
