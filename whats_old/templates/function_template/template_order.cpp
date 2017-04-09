/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Example5
 * Function template order
 *
 * Based on Dimov/Abrahams example
 *
 */

// STEP 0 - incorrect order of templates
// STEP 1 - correct order of templates
// STEP 2 - non template function
#define STEP 0
#include <iostream>

template <typename T>
void foo(T arg)
{
  std::cout << __PRETTY_FUNCTION__ << " (" << arg << ")" << std::endl;
}

#if STEP == 0

// this is full specialization for
//
// template <typename T>
// void foo(T arg)
//
template <>
void foo(int * arg)
{
  std::cout << "Specialized " << __PRETTY_FUNCTION__ << " (" << arg << ")" << std::endl;
}

#endif // STEP == 0

template <typename T>
void foo(T * arg)
{
  std::cout << __PRETTY_FUNCTION__ << " (" << arg << ")" << std::endl;
}

#if STEP == 1 || STEP == 2

// this is full specialization for
//
// template <typename T>
// void foo(T * arg)
//
template <>
void foo(int * arg)
{
  std::cout << "Specialized " << __PRETTY_FUNCTION__ << " (" << arg << ")" << std::endl;
}

#endif // STEP == 1 || STEP == 2

#if STEP == 2

// Non template function is always checked first
void foo(int * arg)
{
  std::cout << "Non template foo(int * arg) (" << arg << ")" << std::endl;
}

#endif // STEP == 2

int main()
{
  int i1 = 1;

  foo(i1);

  int * ptr_i1 = &i1;

  foo(ptr_i1);

  return 0;
}
