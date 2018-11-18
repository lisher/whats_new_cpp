/*
 *
 * What's new in C++
 * Type deduction - auto
 *
 */

#include <iostream>


// Explicit specifying of return type
template <typename RET, typename T, typename U>
RET mul(T t, U u)
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

  std::cout << "mul<double>(" << i << ", " << d << ") == " << mul<double>(i, d) << std::endl;
  std::cout << "mul<double>(" << i << ", " << d << ") == " << mul<double>(d, i) << std::endl;

  return 0;
}
