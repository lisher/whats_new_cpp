/*
 *
 * What's new in C++
 * Type deduction - auto
 *
 */

// STEP 0 - successful compilation
// STEP 1 - same + result of 'quiz'
// STEP 3 - quiz for auto &
// STEP 4 - answers for quiz auto &
#define STEP 4

#define CHECK_TYPE(VAR, TYPE)  if (std::is_same<decltype(VAR), TYPE>::value) { std::cout << "Type of " #VAR << " == " #TYPE << std::endl; }
#define NL std::cout << std::endl

#include <iostream>
#include <type_traits>

void test_auto_by_value()
{
  std::cout << std::endl << __FUNCTION__ << std::endl << std::endl;

  int x = 1;
  const int cx = x;
  const int & rcx = x;
  const int * pcx = &x;
  const int * const cpcx = &x;

  auto ax = x;       // int
  auto acx = cx;     // int
  auto arcx = rcx;   // int
  auto apcx = pcx;   // const int *
  auto acpcx = cpcx; // const int *

  CHECK_TYPE(ax, int);
  CHECK_TYPE(acx, int);
  CHECK_TYPE(arcx, int);
  CHECK_TYPE(apcx, const int *);
  CHECK_TYPE(acpcx, const int *);

  // sanity check
  CHECK_TYPE(apcx, int * const);
  CHECK_TYPE(acpcx, int * const);
  NL;

  std::cout << "     x = " << x <<     "     ax = " << ax << std::endl
            << "    cx = " << cx <<    "    acx = " << acx << std::endl
            << "   rcx = " << rcx <<   "   arcx = " << arcx << std::endl
            << "  *pcx = " << *pcx <<  "  *apcx = " << *apcx << std::endl
            << " *cpcx = " << *cpcx << " *acpcx = " << *acpcx
            << std::endl;

  x = 2;

  std::cout << std::endl << "x = 2;" << std::endl;
  std::cout << "How the values changed?" << std::endl;

#if STEP >= 1
  std::cout << "-------------------------------" << std::endl;
  std::cout << "     x = " << x <<     "     ax = " << ax << std::endl
            << "    cx = " << cx <<    "    acx = " << acx << std::endl
            << "   rcx = " << rcx <<   "   arcx = " << arcx << std::endl
            << "  *pcx = " << *pcx <<  "  *apcx = " << *apcx << std::endl
            << " *cpcx = " << *cpcx << " *acpcx = " << *acpcx
            << std::endl;

  int y = 10;
  ax = 3;
  acx = 4;
  arcx = 5;
  apcx = &y;
  acpcx = &y;

  std::cout << "-------------------------------" << std::endl;
  std::cout << " Let's try to update other values" << std::endl << std::endl;

  std::cout << "     x = " << x <<     "     ax = " << ax << std::endl
            << "    cx = " << cx <<    "    acx = " << acx << std::endl
            << "   rcx = " << rcx <<   "   arcx = " << arcx << std::endl
            << "  *pcx = " << *pcx <<  "  *apcx = " << *apcx << std::endl
            << " *cpcx = " << *cpcx << " *acpcx = " << *acpcx
            << std::endl;

#endif // STEP >= 1
}

void test_auto_by_ref()
{
  std::cout << std::endl << __FUNCTION__ << std::endl << std::endl;

  int x = 1;
  const int cx = x;
  const int & rcx = x;
  const int * pcx = &x;
  const int * const cpcx = &x;

  auto & ax = x;       // int &
  auto & acx = cx;     // const int &
  auto & arcx = rcx;   // const int &
  auto & apcx = pcx;   // const int * &
  auto & acpcx = cpcx; // const int * const &

  CHECK_TYPE(ax, int &);
  CHECK_TYPE(acx, const int &);
  CHECK_TYPE(arcx, const int &);
  CHECK_TYPE(apcx, const int * &);
  CHECK_TYPE(acpcx, const int * const &);

  // sanity check
  CHECK_TYPE(apcx, int * &);
  CHECK_TYPE(acpcx, const int * &);
  NL;

  std::cout << "     x = " << x <<     "     ax = " << ax << std::endl
            << "    cx = " << cx <<    "    acx = " << acx << std::endl
            << "   rcx = " << rcx <<   "   arcx = " << arcx << std::endl
            << "  *pcx = " << *pcx <<  "  *apcx = " << *apcx << std::endl
            << " *cpcx = " << *cpcx << " *acpcx = " << *acpcx
            << std::endl;

  x = 2;

  std::cout << std::endl << "x = 2;" << std::endl;
  std::cout << "How the values changed?" << std::endl;

#if STEP == 4
  std::cout << "-------------------------------" << std::endl;
  std::cout << "     x = " << x <<     "     ax = " << ax << std::endl
            << "    cx = " << cx <<    "    acx = " << acx << std::endl
            << "   rcx = " << rcx <<   "   arcx = " << arcx << std::endl
            << "  *pcx = " << *pcx <<  "  *apcx = " << *apcx << std::endl
            << " *cpcx = " << *cpcx << " *acpcx = " << *acpcx
            << std::endl;

#endif // STEP == 4
}

int main()
{
  test_auto_by_value();

#if STEP == 3 || STEP == 4
  test_auto_by_ref();
#endif

  return 0;
}

