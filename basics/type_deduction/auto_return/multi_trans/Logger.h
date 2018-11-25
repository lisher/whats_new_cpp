/*
 *
 * What's new in C++
 * Type deduction - auto return type
 * How similar it is to templates
 * (c) Lisher
 *
 */

#ifndef WNICPP_LOGGER_H
#define WNICPP_LOGGER_H

#include <iostream>

class Logger
{
  public:
    auto noOfInputs() const
    {
      return 10u;
    }

    auto noOfOutputs() const;

    auto log(float value) const
    {
      std::cout << "Value = " << value << std::endl;
      return value;
    }

    auto logWithDate(float value) const;

    // Note that the following notation is was proposed for C++17
    // auto logWithDate(auto value) const;
};

#endif // WNICPP_LOGGER_H
