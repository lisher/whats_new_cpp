/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Default values of template parameter - functions
 *
 */

// STEP 0 - correct compilation
// STEP 1 - failed type deduction when not all template parameters appear
//          on function parameters list
#define STEP 0

#include <iostream>

template <typename T, typename U = int>
U add(T t, U u)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  return t + u;
}

// Let's try with some simple examples, can we use default value of U parameter?
void tests_1()
{
  // Example 1
  // Full type deduction, both arguments are floats and for these types
  // function will be instantiated from template
  long f1 = 1;
  float f2 = 5.2f;

  std::cout << std::endl << "Example 1" << std::endl;
  std::cout << "add(f1(" << f1 << "), f2(" << f2 << ") = " << add(f1, f2) << std::endl;

  // Example 2
  // Explicit call for specified types, version for requested types will be used

  long c1 = '!';
  char c2 = '#';

  std::cout << std::endl << "Example 2" << std::endl;
  std::cout << "add<long, char>(f1(" << c1 << "), f2(" << c2 << ") = " << add<long, char>(c1, c2) << std::endl;

  // Example 3
  // Specifying only one parameter is not change the fact
  // that the second one will be deduced from provided argument
  long d1 = 9;
  double d2 = 1.1;

  std::cout << std::endl << "Example 3" << std::endl;
  std::cout << "add<double>(d1(" << d1 << "), d2(" << d2 << ") = " << add<double>(d1, d2) << std::endl;
}


// Not all template parameters have to appear on function parameter list

template <typename T, typename U>
U cast(T t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  U u = (U)t;

  return u;
}

void tests_2()
{
  float f1 = 11.1;

  std::cout << std::endl << "Example 4" << std::endl;
  std::cout << "cast<float, int>(f1(" << f1 << ")) = " << cast<float, int>(f1) << std::endl;

#if STEP == 1

  // in this example type deduction will fail for template argument U
  std::cout << "cast(f1(" << f1 << ")) = " << cast(f1) << std::endl;

#endif // STEP == 1

}

// So here default arguments may be useful

template <typename T, typename U = int>
U better_cast(T t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  U u = (U)t;

  return u;
}

void tests_3()
{
  float f1 = 11.1;

  std::cout << std::endl << "Example 5" << std::endl;
  std::cout << "better_cast(f1(" << f1 << ")) = " << better_cast(f1) << std::endl;

  // Unfortunately to explicit specify the target type we need to provide T
  std::cout << "better_cast<float, short>(f1(" << f1 << ")) = "
            << better_cast<float, short>(f1) << std::endl;
}


// In case of templates default argument doesn't have to be
// followed only by parameters with default argument
template <typename U = int, typename T>
U best_cast(T t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  U u = (U)t;

  return u;
}

void tests_4()
{
  float f1 = 7.8;

  std::cout << std::endl << "Example 6" << std::endl;
  std::cout << "best_cast(f1(" << f1 << ")) = " << best_cast(f1) << std::endl;

  std::cout << "best_cast<short>(f1(" << f1 << ")) = " << best_cast<short>(f1) << std::endl;
}


int main()
{
  tests_1();
  tests_2();
  tests_3();
  tests_4();

  return 0;
}
