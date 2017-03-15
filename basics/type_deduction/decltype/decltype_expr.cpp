/*
 *
 * What's new in C++
 * Type deduction - decltype
 *
 */

#include <iostream>

#define CHECK_TYPE(DECL, TYPE) std::cout << (std::is_same<DECL, TYPE>::value ? #DECL " == " #TYPE : #DECL " != " #TYPE) << std::endl
#define NL std::cout << std::endl

template <typename T>
void type_check(T);

//
// PRVALUE
//

class Test
{
  public:
    enum Type
    {
      UNIT,
      MODULE
    };

    Type type;
    double score;
};

Test getTest()
{
  Test test;
  test.score = 4;

  return test;
}

void prvalue()
{
  std::cout << "PRVALUE" << std::endl;

  std::cout << (std::is_same<decltype(1), int>::value ? "decltype(1) == int" : "decltype(1) != int") <<  std::endl;

  // Let's move this pretty printing to macro

  CHECK_TYPE(decltype(1u), int);
  CHECK_TYPE(decltype(1u), unsigned int);
  NL;

  CHECK_TYPE(decltype(1.2), double);
  CHECK_TYPE(decltype(1.3f), float);
  NL;

  CHECK_TYPE(decltype('a'), char);
  NL;

  int x = 4;
  CHECK_TYPE(decltype(&x), int *);
  NL;

  // build-in post incr/decr expressions are prvalues
  CHECK_TYPE(decltype(x++), int);

  std::cout << "Please note that expression is unevaluated so x is still equal " << x << std::endl;

  CHECK_TYPE(decltype(x--), int);
  NL;

  float a = 1.99;
  float b = 3.45;

  // build-in comparison
  CHECK_TYPE(decltype(a<b), bool);
  NL;

  CHECK_TYPE(decltype(getTest()), Test);
  NL;

  // getTest() is rvalue, and numer is not a reference
  CHECK_TYPE(decltype(getTest().score), double);
  NL;
}

//
// LVALUE
//

class HasRef
{
  public:
    HasRef(float& number)
      : number(number)
    {
    }

    float& number;
};

HasRef getHasRef(float& number)
{
  HasRef hasRef(number);

  return hasRef;
}

// But the fact that member is a reference
// doesn't mean that it will outlive the object
class Tricky
{
  public:
    int value = 1;
    int& ref = value;
};

Tricky getTricky()
{
  Tricky tricky;
  return tricky;
}

void lvalue()
{
  std::cout << "LVALUE" << std::endl;

  int x = 1;

  CHECK_TYPE(decltype((x)), int);   // !=
  CHECK_TYPE(decltype((x)), int &);
  NL;

  // but build-id pre incr/dect expressions are lvalues
  CHECK_TYPE(decltype(++x), int);   // !=
  CHECK_TYPE(decltype(++x), int &);
  NL;

  double d1 = 0.0;
  double d2 = 0.0;

  // build-in assignment and compound expressions
  CHECK_TYPE(decltype(d1=d2), double &);
  CHECK_TYPE(decltype(d1+=d2), double &);
  NL;

  int * ptr = &x;
  // Note that address-of expression (&x) is prvalue
  CHECK_TYPE(decltype(*ptr), int&);
  NL;

  CHECK_TYPE(decltype("Hello World!"), const char *);
  CHECK_TYPE(decltype("Hello World!"), const char(&)[13]);
  NL;

  Test test;
  Test * test_ptr = &test;
  CHECK_TYPE(decltype((test.score)), double&);
  CHECK_TYPE(decltype((test_ptr->type)), Test::Type&);
  NL;

  float pi = 3.14;

  // getHasRef(pi) is a rvalue, but member is a reference
  CHECK_TYPE(decltype(getHasRef(pi).number), float&);
  NL;

  // getTricky() is a rvalue, but member is a reference
  CHECK_TYPE(decltype(getTricky().ref), int&);
  NL;
}

//
// XVALUE
//

class Object
{
};

template <typename T>
T&& chooseBest(T&& a, T&& b)
{
  // some decision making...
  return std::forward(a);
}

void xvalue()
{
  std::cout << "XVALUE" << std::endl;

  int x;

  CHECK_TYPE(decltype(std::move(x)), int&&);
  NL;

  CHECK_TYPE(decltype(chooseBest(Object(), Object())), Object&&);
}

int main()
{
  prvalue();
  lvalue();
  xvalue();

  return 0;
}
