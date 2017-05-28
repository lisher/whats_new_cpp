/*
 *
 * What's new in C++
 * rvalue_refs - const lvalue references
 * (c) Lisher
 *
 */

#include <iostream>

class A
{
  public:
    A(std::string name)
      : x(0), name(name)
    {
      std::cout << "["  << name << "] CTOR " <<  __PRETTY_FUNCTION__ << std::endl;

      ++created;
    }
    ~A()
    {
      std::cout << "["  << name << "] " << __PRETTY_FUNCTION__ << std::endl;
    }

    A(const A & rhs)
      : x(rhs.x)
    {
      name = std::string("copy of ") + rhs.name;

      std::cout << "["  << name << "] CTOR " << __PRETTY_FUNCTION__ << std::endl;

      ++created;
    }

    A & operator++()
    {
      ++x;

      return *this;
    }

    A operator++(int) const
    {
      std::cout << "["  << name << "] " << __PRETTY_FUNCTION__ << std::endl;

      A temp("post-incr-temp");
      temp.x = x + 1;

      return temp;
    }

    A operator+(const A & rhs) const
    {
      std::cout << "["  << name << "] " << __PRETTY_FUNCTION__ << std::endl;

      A temp("add-temp");
      temp.x = x + rhs.x;

      return temp;
    }

    int getX() const
    {
      return x;
    }
    std::string getName() const
    {
      return name;
    }

  private:
    int x;
    std::string name;

  public:
    static int created;
};

int A::created = 0;

int main()
{
  std::cout << "Part 1" << std::endl;

  A a1("a1");
  ++a1;

  A a2 = a1;

  std::cout << "{" << a2.getName() << "} x == " << a2.getX() << std::endl << std::endl;


  std::cout << "Part 1" << std::endl;

  A a3 = a1++ + a2++;

  std::cout << "{" << a3.getName() << "} x == " << a3.getX() << std::endl;

  // std::cout << "Number of A objects created = " << A::created << std::endl;

  return 0;
}
