/*
 *
 * What's new in C++
 * Type deduction - auto
 *
 */

// STEP 0 - successful compilation
// STEP 1 - same + result of 'quiz'
// STEP 2 - failed compilation (assign to var under const ptr) + interesting printouts
// STEP 3 - failed compilation (type_check) + interesting printouts
// STEP 4 - exception 1 - non-const ref or ptr to non-const from const var
#define STEP 0

#if STEP == 3
// Function used to check argument type.
// Since it doesn't have definition compiler will protest
// with pretty printout.
// But template uses template type deduction so...
template <typename T>
void type_check(T);

#endif // STEP == 3

#include <iostream>
#include <type_traits>

int main()
{
  int x = 1;
  const int cx = x;
  const int & rcx = x;
  const int * pcx = &x;
  const int * const cpcx = &x;

  auto ax = x;       // int
  auto acx = cx;     // int
  auto arcx = rcx;   // int
  auto apcx = pcx;   // int const *
  auto acpcx = cpcx; // int const *

  // sanity check

  std::cout << "     x = " << x <<     "     ax = " << ax << std::endl
            << "    cx = " << cx <<    "    acx = " << acx << std::endl
            << "   rcx = " << rcx <<   "   arcx = " << arcx << std::endl
            << "  *pcx = " << *pcx <<  "  *apcx = " << *apcx << std::endl
            << " *cpcx = " << *cpcx << " *acpcx = " << *acpcx
            << std::endl;

  x = 2;

  std::cout << std::endl << "x = 2;" << std::endl;
  std::cout << "How the values changed?" << std::endl;

#if STEP == 1
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
  std::cout << "     x = " << x <<     "     ax = " << ax << std::endl
            << "    cx = " << cx <<    "    acx = " << acx << std::endl
            << "   rcx = " << rcx <<   "   arcx = " << arcx << std::endl
            << "  *pcx = " << *pcx <<  "  *apcx = " << *apcx << std::endl
            << " *cpcx = " << *cpcx << " *acpcx = " << *acpcx
            << std::endl;

#endif // STEP == 1

#if STEP == 2

  // let's try to change value of variable under const pointers
  *apcx = 20;
  *acpcx = 30;

#endif // STEP == 2

#if STEP == 3
  // for this variables we can use template to check type
  type_check(apcx);
  type_check(apcx);

  type_check(acpcx);
  type_check(acpcx);

#endif // STEP == 3

#if STEP == 4
  // Exceptions 1
  // auto will not generate reference/pointer that would allow to change const variable
  const int cy = 1;
  auto& e1a = cy;   // const int &
  auto* e1b = &cy;  // const int *

  // Let's check if we const is really enforced
  e1a  = 5;
  *e1b = 6;

#endif // STEP == 4

//TODO example for universal reference needed

  return 0;
}
