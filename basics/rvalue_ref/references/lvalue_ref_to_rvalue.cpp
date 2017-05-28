/*
 *
 * What's new in C++
 * rvalue_refs - lvalue refenrece initialized with rvalue
 * (c) Lisher
 *
 */

#include <iostream>

class A
{
  public:
    A()
      : x(0)
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    ~A()
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    A & get_ref()
    {
      x = 1;

      std::cout << "In function " << __PRETTY_FUNCTION__ << " x == " << this->x << " this == " << this << std::endl;

      return *this;
    }

  public:
    int x;
};

A getA()
{
  return A();
}


int main()
{
  A & reference = getA().get_ref();

  // temporary object A is already destroyed
  // what lies in mmeory under reference is not protected from being overridden
  std::cout << "reference.x = " << reference.x << " &reference = " <<  &reference << std::endl;

  getA().get_ref().x = 3;

  std::cout << "reference.x = " << reference.x << " &reference = " <<  &reference << std::endl;

  // without volatile compiler could skip creating variable
  volatile int y = 10;

  std::cout << "reference.x = " << reference.x << " &reference = " <<  &reference << std::endl;

  reference.x = 8;

  std::cout << "reference.x = " << reference.x << " &reference = " <<  &reference << std::endl;

  std::cout << "y = " << y << " &y = " << (void*)&y << std::endl;

  return 0;
}

