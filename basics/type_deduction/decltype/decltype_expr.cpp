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

class Test
{
  public:
    enum Type
    {
      UNIT,
      MODULE
    };

    Type type;
    int number;
    double score;
};

int main()
{
  //
  // PRVALUE
  //
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
    CHECK_TYPE(decltype(x--), int);
    NL;

    float a = 1.99;
    float b = 3.45;

    // build-in comparison
    CHECK_TYPE(decltype(a<b), bool);
    NL;
  }

  //
  // LVALUE
  //
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

  }

  return 0;
}
