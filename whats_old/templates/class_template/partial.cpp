/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Class template partial specialization
 *
 */

#include <iostream>

template <typename T, typename U>
class MySnapshot
{
  public:
    MySnapshot(const T & first, const U & second)
    {
      this->first = new T(first);
      this->second = new U(second);
    }

    T * first;
    U * second;
};

// partial specialization of class template
template <typename T>
class MySnapshot<T, T>
{
  public:
    MySnapshot(const T & first, const T & second)
    {
      this->first = new T(first);

      if (first == second)
      {
        this->second = NULL;
      }
      else
      {
        this->second = new T(second);
      }
    }

    T * first;
    T * second;
};

template <>
class MySnapshot<char, char>
{
  public:
    MySnapshot(const char & first, const char & second)
    {
      snap += first;
      snap += second;
    }

    std::string snap;
};

// Classes with verbose ctors

class A
{
  public:
    A(int x)
      : x(x)
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    A(const A & rhs)
      : x(rhs.x)
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    bool operator==(const A & rhs) const
    {
      return x == rhs.x;
    }

    int x;
};

// Note instead of B we could make A a template
class B
{
  public:
    B(int x)
      : x(x)
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    B(const B & rhs)
      : x(rhs.x)
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    bool operator==(const B & rhs) const
    {
      return x == rhs.x;
    }

    int x;
};

int main()
{
  A a1(1);
  A a2(1);
  A a3(2);

  B b1(1);

  std::cout << "Now we expect base specialization to be used" << std::endl;
  MySnapshot<A, B>(a1, b1);

  std::cout << "Now we expect partial specialization to be used" << std::endl;
  MySnapshot<A, A>(a1, a2);

  std::cout << "Now we expect partial specialization to be used, but args are different" << std::endl;
  MySnapshot<A, A>(a1, a3);

  char c1('H');
  char c2('e');

  MySnapshot<char, char> letters(c1, c2);
  std::cout << "Full specialization for char = " << letters.snap << std::endl;

  return 0;
}
