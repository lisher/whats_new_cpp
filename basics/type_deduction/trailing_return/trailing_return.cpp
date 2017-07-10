/*
 *
 * What's new in C++
 * Type deduction - auto
 *
 */

#include <iostream>


// STEP 0 - problem definition
// STEP 1 - explicit return type, same calls
// STEP 2 - explicit return type, updated calls
// STEP 3 - decltype, naive way
// STEP 4 - decltype, trailing return type syntax
#define STEP 0

#if STEP == 0

template <typename T, typename U>
T mul(T t, U u)
{
  return t * u;
}

#endif // STEP == 0

#if STEP == 1 || STEP == 2

// Explicit specifying of return type
template <typename RET, typename T, typename U>
RET mul(T t, U u)
{
  return t * u;
}

#endif // STEP == 1 || STEP == 2

#if STEP == 3

// Use decltype to find return type
// Problem? Parsing from left to right,
// variable t and u declarations appear after return type declaration
template <typename T, typename U>
decltype(t * u) mul(T t, U u)
{
  return t * u;
}

#endif // STEP == 3

#if STEP == 4

// Use decltype to find return type, but this time
// using corect syntax
template <typename T, typename U>
auto mul(T t, U u) -> decltype(t * u)
{
  return t * u;
}

#endif // STEP == 4


int main()
{
  int i = 2;
  double d = 1.6;

  std::cout << "int i = 2;" << std::endl;
  std::cout << "double d = 1.6;" << std::endl;
  std::cout << std::endl;

#if STEP == 0 || STEP == 1 || STEP == 3 || STEP == 4
  std::cout << "mul(" << i << ", " << d << ") == " << mul(i, d) << std::endl;
  std::cout << "mul(" << d << ", " << i << ") == " << mul(d, i) << std::endl;
#endif // STEP == 0 || STEP == 1 || STEP == 3 || STEP == 4

#if STEP == 2
  std::cout << "mul<double>(" << i << ", " << d << ") == " << mul<double>(i, d) << std::endl;
  std::cout << "mul<double>(" << i << ", " << d << ") == " << mul<double>(d, i) << std::endl;
#endif // STEP == 2

  return 0;
}
