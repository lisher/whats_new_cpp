/*
 *
 * What's new in C++
 * variadic - variadic template
 *
 * (c) Lisher
 */

#include <cstddef>
#include <iostream>

template <typename... Args>
void createTable(Args... args)
{
  // new operator sizeof... returns the number of parameters in pack
  const size_t size = sizeof...(args) + 2;

  int array[size] = {1, args..., 2};

  for (int value : array)
  {
    std::cout << value << ", ";
  }

  std::cout << std::endl;
}

int main()
{
  createTable(3, 4, 5);

  // narrowing conversion
  createTable(1, 3, 9.1f, 10);

  // Both g++ 5.4 and 7.1 consider this line to be an error
  // while same code in variadic template is reported as warning
  //
  // int array[3] = {1, 'a', 9.1f};

  return 0;
}
