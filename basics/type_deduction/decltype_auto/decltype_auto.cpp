/*
 *
 * What's new in C++
 * Type deduction - decltype(auto)
 *
 */

// STEP 0 - compilation without errors
// STEP 1 - double check types
// STEP 2 - attempt to return reference using auto
#define STEP 0

#include <iostream>

#define CHECK_TYPE(DECL, TYPE) std::cout << (std::is_same<DECL, TYPE>::value ? #DECL " == " #TYPE : #DECL " != " #TYPE) << std::endl
#define NL std::cout << std::endl

// Function used to check argument type.
// Since it doesn't have definition compiler will protest
// with pretty printout.
// But template uses template type deduction so...
template <typename T>
void type_check(T);


void test_variables()
{
  std::cout << std::endl << "----- " <<  __PRETTY_FUNCTION__ << std::endl << std::endl;

  int x = 1;

  auto ax = x;             // int
  decltype(auto) dax = x;  // int

  // let's check is indeed both variables have the same type
  CHECK_TYPE(decltype(ax), decltype(dax));
  NL;

#if STEP == 1

  // and just check if decltypes are not plotting against us
  type_check(ax);
  type_check(dax);

#endif // STEP == 1


  int & ref = x;

  auto aref = ref;             // int
  decltype(auto) daref = ref;  // int &
  decltype(ref) dref = ref;    // int &

  CHECK_TYPE(decltype(aref), int);
  CHECK_TYPE(decltype(daref), int &);
  NL;


  const int & cref = x;

  auto acref = cref;             // int
  decltype(auto) dacref = cref;  // const int &

  CHECK_TYPE(decltype(acref), int);
  CHECK_TYPE(decltype(dacref), const int &);
  NL;


  const int cx = 1;

  // please note that both these statements are equivalent
  decltype(cx) var1 = cx;    // const int
  decltype(auto) var2 = cx;  // const int

  CHECK_TYPE(decltype(var1), decltype(var2));
  CHECK_TYPE(decltype(var1), const int);
  NL;

#if STEP == 1

  // and just check if decltypes are not plotting against us
  //
  // unfortunatelly here trick with template function without
  // definition wont work as intended
  type_check(var1);
  type_check(var2);

#endif // STEP == 1
}

//
// decltype(auto) and functions
//

// let's return to our old problem

// we already know that this version is incorrect
template <typename T, typename U>
T mul1(T t, U u)
{
  return t * u;
}

// this version forces us to repeat the return operand
// which is error prone
template <typename T, typename U>
auto mul2(T t, U u) -> decltype(t + u)
{
  return t * u;
}

// finally with C++14 we can just write
template <typename T, typename U>
auto mul3(T t, U u)
{
  return t * u;
}

// But we are using auto type deduction which will never return reference

void test_multiplications()
{
  std::cout << std::endl << "----- " <<  __PRETTY_FUNCTION__ << std::endl << std::endl;

  int a = 2;
  double b = 3.2;

  std::cout << "mul1(a, b) = " << mul1(a, b) << std::endl;
  std::cout << "mul2(a, b) = " << mul2(a, b) << std::endl;
  std::cout << "mul3(a, b) = " << mul3(a, b) << std::endl;
  std::cout << std::endl;
}

template <typename T>
auto negate(T t)
{
  std::cout << "Called " << __PRETTY_FUNCTION__ << std::endl;
  std::cout << "Arg: " << t << " Return: " << -t << std::endl;

  t = -t;
  return t;
}
void test_neg_by_value()
{
  std::cout << std::endl << "----- " <<  __PRETTY_FUNCTION__ << std::endl << std::endl;

  // let's check it passing argument by value
  int x = 10;
  int y = negate(x);

  std::cout << "x = " << x << " y = " << y << std::endl;
  std::cout << "&x = " << &x << " &y = " << &y << std::endl;
  std::cout << std::endl;

  // next what will happen when we try to pass argument by reference
  int & ref = x;
  y = negate(ref);

  std::cout << "x = " << x << " y = " << y << std::endl;
  std::cout << "&x = " << &x << " &y = " << &y << std::endl;

  // at this point you should know why it doesn't work as expected
}

template <typename T>
auto neg(T & t)
{
  std::cout << "Called " << __PRETTY_FUNCTION__ << std::endl;
  std::cout << "Arg: " << t << " Return: " << -t << std::endl;

  t = -t;
  return t;
}

void test_neg_by_ref()
{
  std::cout << std::endl << "----- " <<  __PRETTY_FUNCTION__ << std::endl << std::endl;

  int x = 10;
  int & ref = x;

  int y = neg(x);

  std::cout << "x = " << x << " y = " << y << std::endl;
  std::cout << "&x = " << &x << " &y = " << &y << std::endl;

  // if argument is a reference and I am returning it
  // the following should be possible

#if STEP == 2
  neg(x) = -5;
#endif // STEP == 2

  // neg(x) is a prvalue
  CHECK_TYPE(decltype(neg(x)), int);
  NL;
}

int main()
{
  test_variables();

  test_multiplications();

  test_neg_by_value();

  test_neg_by_ref();
}
