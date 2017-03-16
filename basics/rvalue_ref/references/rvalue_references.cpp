/*
 *
 * What's new in C++
 * rvalue_refs - rvalue refs
 *
 */

#include <iostream>

// STEP 0 - limitation when creating lvalue/rvalue refs
// STEP 1 - turns off errors from STEP 0
// STEP 2 - functions returning references
// STEP 3 - turns of compilation errors from STEP 2
#define STEP 3

void creating()
{
  int x = 4;

  int & ref = x;
#if STEP == 0
  int&  ref2 = 3;
#endif // STEP == 0
  const int& ref3 = 3;

#if STEP == 0
  int && r_ref = x;
#endif // STEP == 0
  int && r_ref2 = 3;
}


#if STEP >= 2

int & greater(int & a, int & b)
{
  return a > b ? a : b;
}

int less (int a, int b)
{
  return a > b ? b : a;
}

void return_ref()
{
  int width = 80;
  int height = 40;

  std::cout << "width = " << width << " height = " << height << std::endl;

  // function call expression is an lvalue
  greater(width, height) = 60;

  std::cout << "width = " << width << " height = " << height << std::endl;

#if STEP < 3
  // function call expression is an rvalue
  less(width, height) = 80;

  std::cout << "width = " << width << " height = " << height << std::endl;

#endif // STEP < 3
}
#endif // STEP >= 2

int main()
{
  // limitation when creating references
  creating();

  return_ref();

  return 0;
}
