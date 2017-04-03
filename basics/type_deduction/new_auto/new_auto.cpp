/*
 *
 * What's new in C++
 * Type deduction - new auto
 *
 */

#include <iostream>
#include <vector>
#include <type_traits>

// STEP 0 - for build-in types
// STEP 1 - for classes - only ctor arguments
// STEP 2 - with explicit type
// STEP 3 - auto directly from pointer
// STEP 4 - auto with remove_pointer
// STEP 5 - remove_pointer without auto
// STEP 6 - auto with dereference operator
#define STEP 5
#define CHECK_TYPE(DECL, TYPE) std::cout << (std::is_same<DECL, TYPE>::value ? #DECL " == " #TYPE : #DECL " != " #TYPE) << std::endl
#define NL std::cout << std::endl

template <typename T>
void type_check(T);

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

#if STEP == 0
  std::cout << "For build-in type" << std::endl;

  auto my_a = new auto('a');

  CHECK_TYPE(decltype(my_a), char*);
  NL;

  delete my_a;

  auto my_d = new auto(1.9);

  CHECK_TYPE(decltype(my_d), double*);
  NL;

  delete my_d;
#endif // STEP == 0

#if STEP > 0
  std::cout << "For objects" << std::endl;
#endif // STEP > 0

#if STEP == 1
  // this wont work, compiler doesn't know what type to deduce
  auto my_pos = new auto {1.1, 2.2, 3.3};
#endif // STEP == 1

#if STEP == 2
  // this will work, only what's the point?
  auto my_pos = new auto {Position{1.1, 2.2, 3.3}};

  CHECK_TYPE(decltype(my_pos), Position*);

  delete my_pos;
#endif // STEP == 2

#if STEP == 3
  {
    auto start = new Position{1.1, 2.2, 3.3};
    auto stop = new auto(start);

    CHECK_TYPE(decltype(start), Position*);

    CHECK_TYPE(decltype(stop), Position*);
    CHECK_TYPE(decltype(stop), Position**);
    NL;

    delete stop;
    delete start;
  }
#endif // STEP == 3

#if STEP == 4
  {
    auto start = new Position{1.1, 2.2, 3.3};

    // note that         (----------------this----------------------)
    // it a type,
    // not an expr
    auto stop = new auto(std::remove_pointer<decltype(start)>::type);

    delete start;
  }
#endif // STEP == 4

#if STEP == 5
  {
    auto start = new Position{1.1, 2.2, 3.3};

    // note: will call default constructor
    auto stop = new std::remove_pointer<decltype(start)>::type;

    CHECK_TYPE(decltype(stop), Position*);
    NL;

    delete stop;
    delete start;
  }
#endif // STEP == 5

#if STEP == 6
  {
    auto start = new Position{1.1, 2.2, 3.3};

    auto stop = new auto(*start);

    CHECK_TYPE(decltype(stop), Position*);
    NL;

    // please just remember that dereference operator returns reference to
    // data under pointer
    CHECK_TYPE(decltype(*start), Position&);
    NL;

    delete stop;
    delete start;
  }
#endif // STEP == 6

  // add example with explicit reference?
  // add example with non-default constructor
  return 0;
}

