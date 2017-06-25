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

int main()
{
  int number = 4;
  char sign = '+';

  print(number);
  print(sign);

  return 0;
}

