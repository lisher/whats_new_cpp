/*
 *
 * What's new in C++
 * Type deduction - auto
 *
 */

#include <iostream>

template <typename T>
void type_check(T);

typedef int CONST;

class Const
{
  public:
    // this is a function
    const CONST* const getC(const CONST* const arg) const
    { return arg; }

    // this is a pointer to a member function
    const CONST* const (Const::* getCC) (const CONST* const) const;

    // this is a function that returns pointer to a member function
    const CONST* const (Const::* getCCC(const CONST* const))(const CONST* const) const
    { return getCC; }

    // this is a pointer to a member function that returns pointer to a member function
    const CONST* const (Const::* (Const::* constant) (const CONST* const))(const CONST* const) const;


    // C++11 makes it easier?

    // this is a pointer to a member function that returns pointer to a mmeber function
    constexpr static auto (Const::* constant2)(const CONST* const) -> auto(Const::*)(const CONST* const) const -> const CONST* const = &Const::getCCC;

    Const()
    {
      getCC = &Const::getC;
      constant = &Const::getCCC;
    }
};

int main()
{
  int number = 4;

  Const c;
  std::cout << *(c.*((c.*c.constant)(&number)))(&number) << std::endl;

  ++number;
  std::cout << *(c.*((c.*Const::constant2)(&number)))(&number) << std::endl;

  // just for fun
  Const x, y, z;
  ++number;
  std::cout << *(x.*((y.*z.constant)(&number)))(&number) << std::endl;
  return 0;
}
