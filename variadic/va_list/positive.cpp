/*
 *
 * What's new in C++
 * Variadic functions
 *
 */

/*
 * Change the value of STEP identifier to enable different scenarios.
 * Some include code from previous steps, other are completely separate.
 *
 * STEP 0 - calculating average
 * STEP 1 - negative case - no type control
 * STEP 2 - printf - positive
 * STEP 3 - printf - incorrect types marks
 * STEP 4 - no counter provided
 */

#define STEP 4

#include <stdarg.h>
#include <stdio.h>

#include <cstring>
#include <string>
#include <iostream>

double average(int count, ...)
{
  va_list ap;
  double sum = 0;

  va_start(ap, count);

  for (int i = 0 ; i < count ; ++i)
  {
    sum += va_arg(ap, int);
  }

  va_end(ap);

  return sum / count;
}

#if STEP >= 4
// at least one argument must be provided
std::string combine(const char * first, ...)
{
  const char * str = first;
  va_list ap;
  std::string result;

  va_start(ap, first);

  while (strcmp(str, ""))
  {
    result += str;
    str = va_arg(ap, const char *);
  }

  return result;
}
#endif // STEP 4

int main()
{
  printf("%f\n", average(4, 1, 2, 3, 4));

  // access less parameters than provided
  printf("%f\n", average(3, 1, 2, 3, 4));

  // negative scenario
  // access more parameters than provided
  printf("%f\n", average(10, 1, 2, 3, 4));

#if STEP >= 1
  // negative scenario 2
  // no type control in compilation time
  printf("%f\n", average(4, "alpha", 3, -1.5, 'z'));
#endif // STEP 1

#if STEP >= 2
  // classic use - printf
  // positive example

  unsigned u = 4;
  float f = 1.2;
  char c = 'r';

  printf(" unsigned %u, float %f, character %c\n", u, f, c);
#endif // STEP 2

#if STEP == 3
  // compiler supports check of parameters in printf functions (-Wformat)
  printf(" unsigned %u, float %f, character %c\n", f, c, u);
#endif // STEP 3

#if STEP >= 4
  std::cout << "\"" <<  combine("there ", "is ", "no ", "spoon", "") << "\"" <<  std::endl;
#endif // STEP 4

  return 0;
}
