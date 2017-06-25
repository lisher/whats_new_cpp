/*
 *
 * What's new in C++
 * variadic - variadic template
 *
 * (c) Lisher
 */

#include <iostream>

// all good as long as we want to print exactly one argument
template <typename T>
void print(T arg)
{
  std::cout << "Function " << __PRETTY_FUNCTION__ << " called for arg='" << arg << "'" << std::endl;
}

// Option 1: we can provide function that gets single argument
// and doesn't use "recursion"
template <typename First>
void vtPrint(First first)
{
  std::cout << "Function " << __PRETTY_FUNCTION__ << " called for arg='" << first << "'" << std::endl;
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

