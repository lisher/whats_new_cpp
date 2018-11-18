/*
 *
 * What's new in C++
 * Type deduction - auto
 *
 */

#include <iostream>


template <typename T, typename U>
T mul(T t, U u)
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

  std::cout << "mul(" << d << ", " << i << ") == " << mul(d, i) << std::endl;
  std::cout << "mul(" << i << ", " << d << ") == " << mul(i, d) << std::endl;

  return 0;
}
