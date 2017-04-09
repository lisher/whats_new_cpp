/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Example 3
 * Function template specialization
 *
 */

#include <iostream>
#include <cctype>

template<typename T>
bool equal(T a, T b)
{
  std::cout << __PRETTY_FUNCTION__ << " (" << a << ", " << b << ")" << std::endl;

  return a == b;
}

template<>
bool equal<>(char a, char b)
{
  std::cout << __PRETTY_FUNCTION__ << " (" << a << ", " << b << ")" << std::endl;

  return tolower(a) == tolower(b);
}

// pointy brackets next to function name can be skipped
template<>
bool equal(std::string a, std::string b)
{
  std::cout << __PRETTY_FUNCTION__ << " (" << a << ", " << b << ")" << std::endl;

  return tolower(a[0]) == tolower(b[0]);
}

int main()
{
  int i1 = 2;
  int i2 = 3;

  std::cout << "i1 = " << i1 << " i2 = " << i2
            << " equal = " << equal(i1, i2)
            << std::endl;

  char c1 = 'A';
  char c2 = 'a';
  char c3 = 'b';

  std::cout << "c1 = " << c1 << " c2 = " << c2
            << " equal = " << equal(c1, c2)
            << std::endl;

  std::cout << "c2 = " << c2 << " c3 = " << c3
            << " equal = " << equal(c2, c3)
            << std::endl;

  std::string s1 = "Mark";
  std::string s2("Michael");

  std::cout << "s1 = " << s1 << " s2 = " << s2
            << " equal = " << equal(s1, s2)
            << std::endl;

  return 0;
}
