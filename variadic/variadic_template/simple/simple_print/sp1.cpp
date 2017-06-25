/*
 *
 * What's new in C++
 * variadic - variadic template
 *
 * (c) Lisher
 *
 * Note: this example doesn't compile as there is no function
 * vPrint() that can be called with 0 arguments
 */

#include <iostream>

// all good as long as we want to print exactly one argument
template <typename T>
void print(T arg)
{
  std::cout << "Function " << __PRETTY_FUNCTION__ << " called for arg='" << arg << "'" << std::endl;
}

// with variadic template we can provide variable number of agruments
template <typename First, typename... Rest>
void vtPrint(First first, Rest... rest)
{
  std::cout << "Function " << __PRETTY_FUNCTION__ << " called for first='" << first << "' and Rest" << std::endl;
  vtPrint(rest...);
}

int main()
{
  int number = 4;
  char sign = '+';

  print(number);
  print(sign);

  std::cout << std::endl << "Test vtPrint" << std::endl << std::endl;

  vtPrint(number, sign);
  vtPrint(number, sign, "cstring", -12.0);

  return 0;
}

