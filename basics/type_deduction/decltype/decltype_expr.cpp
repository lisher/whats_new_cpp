/*
 *
 * What's new in C++
 * Type deduction - decltype
 *
 */

#include <iostream>

#define CHECK_TYPE(DECL, TYPE) std::cout << (std::is_same<DECL, TYPE>::value ? #DECL " == " #TYPE : #DECL " != " #TYPE) << std::endl
#define NL std::cout << std::endl

int main()
{
  //
  // PRVALUE
  //

  std::cout << (std::is_same<decltype(1), int>::value ? "decltype(1) == int" : "decltype(1) != int") <<  std::endl;

  // Let's move this pretty printing to macro

  CHECK_TYPE(decltype(1u), int);
  CHECK_TYPE(decltype(1u), unsigned int);
  NL;

  CHECK_TYPE(decltype(1.2), double);
  CHECK_TYPE(decltype(1.3f), float);
  NL;

  CHECK_TYPE(decltype('a'), char);
  NL;

  int x = 4;
  CHECK_TYPE(decltype(&x), int *);
  NL;

  // build-in post incr/decr expressions are prvalues
  CHECK_TYPE(decltype(x++), int);
  CHECK_TYPE(decltype(x--), int);
  NL;


  //
  // LVALUE
  //

  CHECK_TYPE(decltype((x)), int);
  CHECK_TYPE(decltype((x)), int &);
  NL;

  // but build-id pre incr/dect expressions are lvalues
  CHECK_TYPE(decltype(++x), int);
  CHECK_TYPE(decltype(++x), int &);
  NL;
  return 0;
}
