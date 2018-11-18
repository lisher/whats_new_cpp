/*
 *
 * What's new in C++
 * Type deduction - auto
 *
 */

#include <iostream>

// Use decltype to find return type
// Problem? Parsing from left to right,
// variable t and u declarations appear after return type declaration
template <typename T, typename U>
decltype(t * u) mul(T t, U u)
{
  return t * u;
}

int main()
{
  int i = 2;
  double d = 1.6;

  std::cout << "int i = 2;" << std::endl;
  std::cout << "double d = 1.6;" << std::endl;
  std::cout << std::endl;

  std::cout << "mul(" << i << ", " << d << ") == " << mul(i, d) << std::endl;
  std::cout << "mul(" << d << ", " << i << ") == " << mul(d, i) << std::endl;

  return 0;
}
