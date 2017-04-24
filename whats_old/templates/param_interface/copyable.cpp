/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Template parameter interface - copyable
 *
 */

// STEP 0 - container of Copyable
// STEP 1 - container of NotCopyable
#define STEP 0

#include <cstddef>
#include <iostream>

template <typename T, size_t S>
class Container
{
  public:
    Container()
    {
      for (size_t i = 0 ; i < S ; ++i)
      {
        array[i] = NULL;
      }
    }

    ~Container()
    {
      for (size_t i = 0 ; i < S ; ++i)
      {
        if (array[i])
        {
          array[i] = NULL;
        }
      }
    }

    void add(size_t pos, const T & data)
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;

      if (pos < S)
      {
        if (array[pos] != NULL)
        {
          delete array[pos];
        }

        array[pos] = new T(data);
      }
    }

    void log()
    {
      std::cout << "Container {";
      for (size_t i = 0 ; i < S ; ++i)
      {
        if (array[i] == NULL)
        {
          std::cout << "(NULL)";
        }
        else
        {
          std::cout << "(" << *array[i] << ")";
        }
      }
      std::cout << "}" << std::endl;
    }
  private:
    T* array[S];
};

#if STEP == 1
class Copyable
{
  public:
    Copyable(int value)
      : value(value)
    {
    }
    Copyable(const Copyable & rhs)
      : value(rhs.value)
    {
    }

  private:
    int value;

    friend std::ostream & operator<<(std::ostream & stream, const Copyable & copyable);
};

std::ostream & operator<<(std::ostream & stream, const Copyable & copyable)
{
  return stream << copyable.value;
}
#endif // STEP == 1

#if STEP == 2
class NotCopyable
{
  public:
    NotCopyable(int value)
      : value(value)
    {
    }

  private:
    NotCopyable(const NotCopyable & rhs)
      : value(rhs.value)
    {
    }
    NotCopyable & operator=(const NotCopyable & rhs)
    {
      value = rhs.value;
      return *this;
    }

  private:
    int value;

    friend std::ostream & operator<<(std::ostream & stream, const NotCopyable & notcopyable);
};
std::ostream & operator<<(std::ostream & stream, const NotCopyable & notcopyable)
{
  return stream << notcopyable.value;
}
#endif // STEP == 2


int main()
{
  Container <int, 3> con0;

  int i1 = 10;
  int i2 = 12;

  con0.add(1, i1);
  con0.add(2, i2);

  con0.log();

#if STEP == 1
  Container<Copyable, 5> con1;

  Copyable a(21);
  Copyable b(22);

  con1.add(0, a);
  con1.add(1, b);

  con1.log();
#endif // STEP == 1

#if STEP == 2
  Container<NotCopyable, 4> con2;

  NotCopyable x(100);
  NotCopyable y(101);

  con2.add(0, x);
  con2.add(1, y);
#endif // STEP == 2

  return 0;
}

