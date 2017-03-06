/*
 *
 * What's new in C++
 * Type deduction - decltype
 *
 */

// STEP 0 - successful compilation
// STEP 1 - same + result of 'quiz'
// STEP 2 - check types using is_same<>
#define STEP 2

#include <iostream>

int main()
{
  int x = 1;
  const int cx = x;
  const int & rcx = x;
  const int * pcx = &x;
  const int * const cpcx = &x;

  decltype(x) dx       = x;       // int
  decltype(cx) dcx     = cx;      // const int
  decltype(rcx) drcx   = rcx;     // const int &
  decltype(pcx) dpcx   = pcx;     // const int *
  decltype(cpcx) dcpcx = cpcx;    // const int * const

  std::cout << "     x = " << x <<     "     dx = " << dx << std::endl
            << "    cx = " << cx <<    "    dcx = " << dcx << std::endl
            << "   rcx = " << rcx <<   "   drcx = " << drcx << std::endl
            << "  *pcx = " << *pcx <<  "  *dpcx = " << *dpcx << std::endl
            << " *cpcx = " << *cpcx << " *dcpcx = " << *dcpcx
            << std::endl;

  x = 2;

  std::cout << std::endl << "x = 2;" << std::endl;
  std::cout << "How the values changed?" << std::endl;

#if STEP == 1

  std::cout << "-------------------------------" << std::endl;
  std::cout << "     x = " << x <<     "     dx = " << dx << std::endl
            << "    cx = " << cx <<    "    dcx = " << dcx << std::endl
            << "   rcx = " << rcx <<   "   drcx = " << drcx << std::endl
            << "  *pcx = " << *pcx <<  "  *dpcx = " << *dpcx << std::endl
            << " *cpcx = " << *cpcx << " *dcpcx = " << *dcpcx
            << std::endl;

  int y = 10;
  dx = 3;
  // dcx = 4;    // is const
  // drcx = 5;   // is const
  dpcx = &y;
  // dcpcx = &y; // is const

  std::cout << "-------------------------------" << std::endl;
  std::cout << "     x = " << x <<     "     dx = " << dx << std::endl
            << "    cx = " << cx <<    "    dcx = " << dcx << std::endl
            << "   rcx = " << rcx <<   "   drcx = " << drcx << std::endl
            << "  *pcx = " << *pcx <<  "  dapcx = " << *dpcx << std::endl
            << " *cpcx = " << *cpcx << " *dcpcx = " << *dcpcx
            << std::endl;

#endif // STEP == 1

#if STEP == 2

  std::cout << std::endl << "Let's check the types using is_same<> template"
            << std::endl << "-------------------------------" << std::endl;

  std::cout << (std::is_same<decltype(dx), int>::value
                ? "dx type = int"
                : "dx type != int")
            << std::endl;
  std::cout << (std::is_same<decltype(dcx), const int>::value
                ? "dcx type = const int"
                : "dcx type != const int")
            << std::endl;
  std::cout << (std::is_same<decltype(drcx), const int &>::value
                ? "drcx type = const int &"
                : "drcx type != const int &")
            << std::endl;
  std::cout << (std::is_same<decltype(dpcx), const int *>::value
                ? "dpcx type = const int *"
                : "dpcx type != const int *")
            << std::endl;
  std::cout << (std::is_same<decltype(dcpcx), const int * /*const*/>::value
                ? "dcpcx type = const int * const"
                : "dcpcx type != const int * const")
            << std::endl;

  // Question
  // But if auto uses the template type deduction why these examples work?
  // Shouldn't they drop references and consts?
  //
  // Hint
  // Is type deduction really needed here?
#endif // STEP == 2

  return 0;
}
