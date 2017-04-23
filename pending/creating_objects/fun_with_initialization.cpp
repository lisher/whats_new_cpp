/*
 * What's ???
 * (c) Lisher
 *
 * Need to be added to some topic
 *
 */

// STEP 0 - correct code
// STEP 1 - function declaration in main
#define STEP 2

#define IO_ENABLED 1

#if IO_ENABLED == 1

#include <iostream>

#endif

class NoCtors
{
  public:
    int i;
    char c;
    double d;
};

void fun(NoCtors & obj)
{
  if (obj.i == 0)
  {
    int x = 0;
  }
}

#if IO_ENABLED == 1
std::ostream & operator<< (std::ostream & stream, const NoCtors & obj)
{
  return stream << "NoCtors i = " << obj.i << " c = {'" << obj.c << "', " << std::hex << (int)obj.c << "} d = " << obj.d << std::endl;
}
#endif // IO_ENABLED == 1

int main()
{
  // compiler-provided default constructor will not
  // initialize members
  NoCtors nc1;
  fun(nc1);

#if IO_ENABLED == 1
  std::cout << nc1 << std::endl;
#endif // IO_ENABLED == 1

#if STEP == 1
  NoCtors nc2();

#if IO_ENABLED == 1
  std::cout << nc2 << std::endl;
#endif // IO_ENABLED == 1

#endif // STEP == 1

#if STEP == 2
  NoCtors nc3 = NoCtors();
  fun(nc3);

#if IO_ENABLED == 1
  std::cout << nc3 << std::endl;
#endif // IO_ENABLED == 1

#endif // STEP == 2

  return 0;
}

