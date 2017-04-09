/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Example 2
 * Function template overloading
 *
 */

#include <iostream>

template<typename T, typename U>
bool my_greater(T lhs, U rhs)
{
  std::cout << __PRETTY_FUNCTION__ << " (" << lhs << ", " << rhs << ")" << std::endl;

  return lhs > rhs;
}

template<typename T>
bool my_greater(T lhs, T rhs)
{
  std::cout << __PRETTY_FUNCTION__ << " (" << lhs << ", " << rhs << ")" << std::endl;

  return lhs > rhs;
}

int main()
{
  int i1 = 1;
  int i2 = 2;

  // two ints
  bool b1 = my_greater(i1,i2);

  float f1 = 1.2;
  float f2 = 1.3;

  // two floats
  bool b2 = my_greater(f1,f2);

  // float and int, note that if my_greater<int, int> was called
  // result whould be false
  bool b3 = my_greater(f1, i1);

  // note that templates have different number of arguments
  bool b4 = my_greater<int, int>(f1, i1);

  double d1 = 2.0;

  // double and int
  bool b5 = my_greater(d1, i2);

  std::cout << "b1 = " << std::boolalpha << b1 << std::endl;
  std::cout << "b2 = " << std::boolalpha << b2 << std::endl;
  std::cout << "b3 = " << std::boolalpha << b3 << std::endl;
  std::cout << "b4 = " << std::boolalpha << b4 << std::endl;
  std::cout << "b5 = " << std::boolalpha << b5 << std::endl;

  return 0;
}
