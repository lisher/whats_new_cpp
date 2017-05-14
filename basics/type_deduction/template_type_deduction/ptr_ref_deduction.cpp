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
#define CHECK_TYPE(VAR, TYPE)  if (std::is_same<decltype(VAR), TYPE>::value) { std::cout << "Type of " #VAR << " == " #TYPE << std::endl; }

#define CALL(CMD) std::cout << "Call : " #CMD << std::endl; CMD;

#define NL std::cout << std::endl

#include <iostream>

template <typename T>
T & pass_ref(T & t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  CHECK_TYPE(t, int);
  CHECK_TYPE(t, int &);
  CHECK_TYPE(t, const int &);

  CHECK_TYPE(t, int * &);
  CHECK_TYPE(t, int * const &);
  CHECK_TYPE(t, const int * &);
  CHECK_TYPE(t, const int * const &);

  CHECK_TYPE(t, int *);
  CHECK_TYPE(t, const int *);
  CHECK_TYPE(t, int * const);
  CHECK_TYPE(t, const int * const);
  NL;

  return t;
}

// crx - const reference to x
// pcx - pointer to const x
// cpx - const pointer to x
// cpcx - const pointer to const x

void test_references()
{
  std::cout << std::endl << __FUNCTION__ << std::endl << std::endl;

  // values and references
  int x = 1;
  int & rx = x;
  const int cx = x;
  const int & crx = x;

  // pointers
  int * px = &x;
  const int * pcx = &x;
  int * const cpx = &x;
  const int * const cpcx = &x;

  // references to pointers
  const int * & rpcx = pcx;
  int * const & rcpx = cpx;
  const int * const & rcpcx = cpcx;

  CALL(  pass_ref(x)  );     // T = int                 ParamType = int &
  CALL(  pass_ref(rx)  );    // T = int                 ParamType = int &
  CALL(  pass_ref(cx)  );    // T = const int           ParamType = const int &
  CALL(  pass_ref(crx)  );   // T = const int           ParamType = const int &

  CALL(  pass_ref(px)  );    // T = int *               ParamType = int * &
  CALL(  pass_ref(pcx)  );   // T = const int *         ParamType = const int * &
  CALL(  pass_ref(cpx)  );   // T = int * const         ParamType = int * const &
  CALL(  pass_ref(cpcx)  );  // T = const int * const   ParamType = const int * const &

  CALL(  pass_ref(rpcx)  );  // T = const int *         ParamType = const int * &
  CALL(  pass_ref(rcpx)  );  // T = int * const         ParamType = int * const &
  CALL(  pass_ref(rcpcx)  ); // T = const int * const   ParamType = const int * const &
}

template <typename T>
T* pass_ptr(T * t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  CHECK_TYPE(t, int);
  CHECK_TYPE(t, int &);
  CHECK_TYPE(t, const int &);

  CHECK_TYPE(t, int * &);
  CHECK_TYPE(t, int * const &);
  CHECK_TYPE(t, const int * &);
  CHECK_TYPE(t, const int * const &);

  CHECK_TYPE(t, int *);
  CHECK_TYPE(t, const int *);
  CHECK_TYPE(t, int * const);
  CHECK_TYPE(t, const int * const);
  NL;

  return t;
}

void test_pointers()
{
  std::cout << std::endl << __FUNCTION__ << std::endl << std::endl;

  // pointers
  int x = 1;
  int * px = &x;
  const int * pcx = &x;
  int * const cpx = &x;
  const int * const cpcx = &x;

  // references to pointers
  const int * & rpcx = pcx;
  int * const & rcpx = cpx;
  const int * const & rcpcx = cpcx;

  CALL(  pass_ptr(px)  );   // T = int                 ParamType = int *
  CALL(  pass_ptr(pcx)  );  // T = const int           ParamType = const int *
  CALL(  pass_ptr(cpx)  );  // T = int                 ParamType = int *
  CALL(  pass_ptr(cpcx)  ); // T = const int           ParamType = const int *

  CALL(  pass_ptr(rpcx)  );  // T = const int           ParamType = const int *
  CALL(  pass_ptr(rcpx)  );  // T = int                 ParamType = int *
  CALL(  pass_ptr(rcpcx)  ); // T = const int           ParamType = const int *
}

template <typename T>
T pass_val(T t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  CHECK_TYPE(t, int);
  CHECK_TYPE(t, int &);
  CHECK_TYPE(t, const int &);

  CHECK_TYPE(t, int * &);
  CHECK_TYPE(t, int * const &);
  CHECK_TYPE(t, const int * &);
  CHECK_TYPE(t, const int * const &);

  CHECK_TYPE(t, int *);
  CHECK_TYPE(t, const int *);
  CHECK_TYPE(t, int * const);
  CHECK_TYPE(t, const int * const);
  NL;

  return t;
}

void test_values()
{
  std::cout << std::endl << __FUNCTION__ << std::endl << std::endl;

  int x = 1;
  int & rx = x;
  const int cx = x;
  const int & crx = x;
  int * px = &x;
  const int * pcx = &x;
  int * const cpx = &x;
  const int * const cpcx = &x;

  CALL(  pass_val(x)  );    // T = int                 ParamType = int
  CALL(  pass_val(rx)  );   // T = int                 ParamType = int
  CALL(  pass_val(cx)  );   // T = int                 ParamType = int
  CALL(  pass_val(crx)  );  // T = int                 ParamType = int
  CALL(  pass_val(px)  );   // T = int *               ParamType = int *
  CALL(  pass_val(pcx)  );  // T = const int *         ParamType = const int *
  CALL(  pass_val(cpx)  );  // T = int *               ParamType = int *
  CALL(  pass_val(cpcx)  ); // T = const int *         ParamType = const int *
}


template <typename T>
const T* pass_const_ptr(const T * t)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  CHECK_TYPE(t, int);
  CHECK_TYPE(t, int &);
  CHECK_TYPE(t, const int &);

  CHECK_TYPE(t, int * &);
  CHECK_TYPE(t, int * const &);
  CHECK_TYPE(t, const int * &);
  CHECK_TYPE(t, const int * const &);

  CHECK_TYPE(t, int *);
  CHECK_TYPE(t, const int *);
  CHECK_TYPE(t, int * const);
  CHECK_TYPE(t, const int * const);
  NL;

  return t;
}

void test_const_pointers()
{
  std::cout << std::endl << __FUNCTION__ << std::endl << std::endl;

  // pointers
  int x = 1;
  int * px = &x;
  const int * pcx = &x;
  int * const cpx = &x;
  const int * const cpcx = &x;

  // references to pointers
  const int * & rpcx = pcx;
  int * const & rcpx = cpx;
  const int * const & rcpcx = cpcx;

  CALL(  pass_const_ptr(px)  );    // T = int                 ParamType = const int *
  CALL(  pass_const_ptr(pcx)  );   // T = int                 ParamType = const int *
  CALL(  pass_const_ptr(cpx)  );   // T = int                 ParamType = const int *
  CALL(  pass_const_ptr(cpcx)  );  // T = int                 ParamType = const int *

  CALL(  pass_const_ptr(rpcx)  );  // T = int                 ParamType = const int *
  CALL(  pass_const_ptr(rcpx)  );  // T = int                 ParamType = const int *
  CALL(  pass_const_ptr(rcpcx)  ); // T = int                 ParamType = const int *
}

int main()
{
  test_references();

  test_pointers();

  test_values();

  test_const_pointers();
}

