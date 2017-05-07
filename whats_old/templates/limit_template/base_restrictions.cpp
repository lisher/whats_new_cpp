/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Limitation on templates
 *
 * Note: enable_if or concepts would be a better tool here
 *
 */

// STEP 0 - correct compilation
// STEP 1 - call when overloaded operator is not available
// STEP 2 - full specialization using to_string
// STEP 3 - missing definition for specialization
// STEP 4 - deleted specialization
#define STEP 0

#include <iostream>

template <typename T, typename U>
T add(T t, U u)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  return t + u;
}

void use_anything()
{
  std::cout << "Use anything as argument" << std::endl << std::endl;

  // let's try with something already checked
  int i1 = 5;
  double d1 = 7.4;

  std::cout << "add(i1, d1) = " << add(i1, d1)
            << " is not the same as add(d1, i1) = " << add(d1, i1)
            << std::endl << std::endl;

  // string has operator+(string) so this should also be possible
  std::string name("Mark");
  std::string nickname(" the Looser");

  std::cout << add(name, nickname) << std::endl;

#if STEP == 1
  // but operator+(int) is not available
  std::string family("Celeron ");
  int number = 2;

  std::cout << add(family, number) << std::endl;
#endif // STEP == 1
}

#if STEP == 2
// How can we prevent such errors? Well we can't if we don't provide
// specialization that will merge string and int correctly like below
//
// We could leave U as only template parameter, but functions to_string
// can handle only build-in types

template<>
std::string add(std::string t, int u)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  // Functions to_string are available since C++11
  return t + std::to_string(u);
}

void adding_int_to_string_with_full_spec()
{
  std::string family("Celeron ");
  int number = 2;

  std::cout << add(family, number) << std::endl;
}
#endif // STEP == 2

#if STEP == 3
// But that was also known to us. So let's say we want to prevent compilation but
// with a little more descriptive message

// Option 1
// If we provide specialization without definition compilation will fail

template <>
std::string add(std::string t, int u);

void missing_definition()
{
  std::string family("Celeron ");
  int number = 2;

  std::cout << add(family, number) << std::endl;
}
#endif // STEP == 3

#if STEP == 4
// With C++11 we can mark specialization as deleted
//
// Just for fun we apply it to new base template specialization
// that accepts string as first parameter and any type for second parameter

template <typename U>
U add(std::string t, U u) = delete;

void deleted_specialization()
{
  std::string family("Celeron ");
  int number = 2;

  std::cout << add(family, number) << std::endl;
}
#endif // STEP == 4

int main()
{
  use_anything();
#if STEP == 2
  adding_int_to_string_with_full_spec();
#endif // STEP == 2

#if STEP == 3
  missing_definition();
#endif // STEP == 3

#if STEP == 4
  deleted_definition();
#endif // STEP == 4
}

