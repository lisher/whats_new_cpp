/*
 *
 * What's new in C++
 * variadic - variadic template
 *
 * (c) Lisher
 */

/*
 * STEP 0 - templates, reminder
 * STEP 1 - variadic template without stop stop point
 * STEP 2 - added missing stop point
 * STEP 3 - alternative stop point
 */

#define STEP 0

#include <iostream>

// all good as long as we want to print exactly one argument
template <typename T>
void print(T arg)
{
  std::cout << "Function " << __PRETTY_FUNCTION__ << " called for arg='" << arg << "'" << std::endl;
}

#if STEP == 2

template <typename First>
void vtPrint(First first)
{
  std::cout << "Function " << __PRETTY_FUNCTION__ << " called for arg='" << first << "'" << std::endl;
}

#endif

#if STEP >= 3

void vtPrint()
{
  std::cout << "Function " << __PRETTY_FUNCTION__ << " called without arguments" << std::endl;
}

#endif

#if STEP >= 1

// with variadic template we can provide variable number of agruments
template <typename First, typename... Rest>
void vtPrint(First first, Rest... rest)
{
  std::cout << "Function " << __PRETTY_FUNCTION__ << " called for first='" << first << "' and Rest" << std::endl;
  vtPrint(rest...);
}

#endif


int main()
{
  int number = 4;
  char sign = '+';

  print(number);
  print(sign);

#if STEP >= 1

  std::cout << std::endl << "Test vtPrint" << std::endl << std::endl;

  vtPrint(number, sign);
  vtPrint(number, sign, "cstring", -12.0);

#endif

  return 0;
}

