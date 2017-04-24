/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Class template - more complex example
 *  - member definition outside class
 *  - template function in template class
 *  - specializations for above
 *
 */

// STEP 0 - correct code
// STEP 1 - attempt to specialize only member function
#define STEP 0

#include <iostream>
template <typename T, typename U>
class A
{
  public:
    // Not all template parameters have to be used in ctor
    A(T value)
      : first(value), second()
    {
    }

    // function definition outside class definition
    U getSecond();

    // template functions can introduce new template parameter
    template <typename X>
    void add (X x);

  private:
    T first;
    U second;
};

template <typename T, typename U>
U A<T, U>::getSecond()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  return second;
}

// It is possible to provide specialization for specified member
template <>
int A<char, int>::getSecond()
{
  std::cout << "Specialized " << __PRETTY_FUNCTION__ << std::endl;

  return second;
}

template <typename T, typename U>
template <typename X>
void A<T, U>::add(X x)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  second += x;
}

#if STEP == 1

// unfortunately it is not possible to specialize only member function
template <typename T, typename U>
template <>
void A<T, U>::add(int x)
{
  std::cout << "Specialized " << __PRETTY_FUNCTION__ << std::endl;

  second += x;
}

#endif // STEP == 1

template <>
template <>
void A<char, int>::add(int x)
{
  std::cout << "Specialized " << __PRETTY_FUNCTION__ << std::endl;

  second += x;
}

int main()
{
  A<char, int> a('a');

  std::cout << "a.getSecond() = " << a.getSecond() << std::endl << std::endl;

  a.add(12.0);

  std::cout << "a.getSecond() = " << a.getSecond() << std::endl << std::endl;

  a.add(12);

  std::cout << "a.getSecond() = " << a.getSecond() << std::endl << std::endl;

  std::cout << "---- Different class ----" << std::endl << std::endl;

  A<double, float> a2(21.2);

  std::cout << "a2.getSecond() = " << a2.getSecond() << std::endl << std::endl;

  a2.add(7);

  std::cout << "a2.getSecond() = " << a2.getSecond() << std::endl << std::endl;

  return 0;
}

