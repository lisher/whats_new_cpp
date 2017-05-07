/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Function signature
 *
 */

// STEP 0 - successful compilation
// STEP 1 - ambiguous functions
#define STEP 0

#include <iostream>

// these two function can coexist because they have different signatures
int avg(int a, int b)
{
  return (a + b) / 2;
}

float avg(float a, float b)
{
  return (a + b) / 2;
}

void peaceful_coexistence()
{
  std::cout << "avg(3, 4) = " << avg(3, 4) << std::endl;

  std::cout << "avg(3.0f, 4.0f) = " << avg(3.0f, 4.0f) << std::endl;
}

#if STEP == 1

// this function will cause ambiguousness
// since it has the same signature as
// int avg(int, int)
double avg(int a, int b)
{
  return (a + b) / 2.0;
}

#endif // STEP == 1

int main()
{
  peaceful_coexistence();

  return 0;
}
