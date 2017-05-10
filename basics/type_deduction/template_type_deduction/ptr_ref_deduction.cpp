/*
 * What's new in C++
 * Type deduction
 * (c) Lisher
 *
 * Template type dedution for pointers and references
 *
 */

// Simple macro that uses template std::is_same and decltype to detect
// if variable has given type
// Note that since both template arguments are specified
// no type deduction will be performed
#define CHECK_TYPE(VAR, TYPE) std::cout << "Type of " #VAR << (std::is_same<decltype(VAR), TYPE>::value ? " == " #TYPE : " != " #TYPE) << std::endl
#define NL std::cout << std::endl

#include <iostream>

template <typename T>
T pass(T & t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  CHECK_TYPE(t, int &);
  CHECK_TYPE(t, const int &);
  CHECK_TYPE(t, int * &);
  CHECK_TYPE(t, int * const &);
  CHECK_TYPE(t, const int * &);
  CHECK_TYPE(t, const int * const &);
  NL;

  return t;
}

void test_references()
{
  std::cout << std::endl << __FUNCTION__ << std::endl << std::endl;

  int x = 1;
  const int cx = x;
  const int & rcx = x;
  int * px = &x;
  const int * pcx = &x;
  int * const cpx = &x;
  const int * const cpcx = &x;

  pass(x);    // T = int                 ParamType = int &
  pass(cx);   // T = const int           ParamType = const int &
  pass(rcx);  // T = const int           ParamType = const int &
  pass(px);   // T = int *               ParamType = int * &
  pass(pcx);  // T = const int *         ParamType = const int * &
  pass(cpx);  // T = int * const         ParamType = int * const &
  pass(cpcx); // T = const int * const   ParamType = const int * const &
}

template <typename T>
T* pass2(T * t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  CHECK_TYPE(t, int *);
  CHECK_TYPE(t, const int *);
  CHECK_TYPE(t, const int * const);
  NL;

  return t;
}

void test_pointers()
{
  std::cout << std::endl << __FUNCTION__ << std::endl << std::endl;

  int x = 1;
  int * px = &x;
  const int * pcx = &x;
  int * const cpx = &x;
  const int * const cpcx = &x;


  pass2(px);   // T = int                 ParamType = int *
  pass2(pcx);  // T = const int           ParamType = const int *
  pass2(cpx);  // T = int                 ParamType = int &
  pass2(pcx);  // T = const int           ParamType = const int *
  pass2(cpcx); // T = const int           ParamType = const int *
}

int main()
{
  test_references();

  test_pointers();
}

