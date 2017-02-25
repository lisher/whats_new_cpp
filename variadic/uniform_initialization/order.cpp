/*
 *
 * What's new in C++
 * Uniform initialization
 *
 */

/*
 * STEP 0
 * STEP 1 - class with private member
 * STEP 2 - class with user defined ctor with diff no of params
 */
#define STEP 2

#include <iostream>

// Aggregate
class A
{
  public:
    void print()
    {
      std::cout << "A = {i=" << i << " c='" << c << "'}" << std::endl;
    }

    int i;
    char c;
};

// Class with different ctor parameters order
// than member order
// Note 1: order on initialization list have to be the same as
// order of member in class
// Note 2: not an aggregate, user defined ctor
class B
{
  public:
    void print()
    {
      std::cout << "B = {i=" << i << " c='" << c << "'}" << std::endl;
    }

    B(char c, int i)
      : i(i), c(c)
    {}

    // mmebers are public
    int i;
    char c;
};

#if STEP == 1

// Class with private members
// Not an aggregate, private member
class C
{
  public:
    void print()
    {
      std::cout << "C = {i=" << i << " c='" << c << "'}" << std::endl;
    }

  private:
    int i;
    char c;
};

#endif // STEP == 1

#if STEP == 2

// Class with constructor with different number of parameters
// than members
// Note: user defined ctor
class D
{
  public:
    void print()
    {
      std::cout << "d = {i=" << i << " c='" << c << "'}" << std::endl;
    }

  public:
    D(int first)
    {
      // stuff
    }

    int i;
    char c;
};

#endif // STEP == 2

int main()
{
  A a{65, '4'};
  a.print();

  B b1{65, '4'};
  b1.print();

  B b2{'4', 65};
  b2.print();

#if STEP == 1

  C c{65, '4'};
  c.print();

#endif // STEP == 1

#if STEP == 2

  D d{65, '4'};
  d.print();

#endif // STEP == 2

  return 0;
}
