/*
 *
 * What's new in C++
 * Type deduction - new auto
 *
 */

#include <iostream>
#include <vector>
#include <type_traits>

// STEP 2 - with explicit type

#define CHECK_TYPE(VAR, TYPE) std::cout << (std::is_same<decltype(VAR), TYPE>::value ? #VAR " is " #TYPE : #VAR " isn't " #TYPE) << std::endl
#define NL std::cout << std::endl

template <typename T>
void type_check(T);

// Class with loud constructors
class Position
{
  public:
    Position()
    {
      std::cout << "Function " << __PRETTY_FUNCTION__ << " called" << std::endl;
    }

    Position(double x, double y, double z)
      : x(x), y(y), z(z)
    {
      std::cout << "Function " << __PRETTY_FUNCTION__ << " called" << std::endl;
    }

    Position(const Position & rhs)
      : x(rhs.x), y(rhs.y), z(rhs.z)
    {
      std::cout << "Function " << __PRETTY_FUNCTION__ << " called" << std::endl;
    }

  private:
    double x, y, z;
};

int main()
{
  std::cout << "For objects" << std::endl;

  // this will work, only what's the point?
  auto my_pos = new auto {Position{1.1, 2.2, 3.3}};

  CHECK_TYPE(my_pos, Position*);

  delete my_pos;

  return 0;
}

