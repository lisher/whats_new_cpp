/*
 *
 * What's new in C++
 * Type deduction - auto
 * (c) Lisher
 *
 */

#include <iostream>

// same problem as in example for trailing return type syntax
// with C++14 much simpler solution is availabe
template <typename T, typename U>
auto mul(T t, U u)
{
  return t * u;
}

// Example with auto return of iterator ??
class Container
{
  public:
    class iterator
    {
      public:
        iterator()
          : ptr(nullptr)
        {
        }

        iterator(const iterator& rhs)
          : ptr(rhs.ptr)
        {
        }

        bool operator!=(const iterator& rhs)
        {
          return ptr != rhs.ptr;
        }

        iterator operator++()
        {
          iterator temp(*this);

          ++ptr;

          return temp;
        }
        uint8_t& operator*()
        {
          return *ptr;
        }

      private:
        iterator(uint8_t* ptr)
         : ptr(ptr)
        {
        }

        uint8_t* ptr;

        friend Container;
    };

    // begin() and end() need to be placed before
    // copy ctor
    auto begin()
    {
      return iterator(buffer);
    }
    auto end()
    {
      return iterator(buffer + size);
    }

    Container(size_t size)
      : size(size)
    {
      buffer = new uint8_t[size];

      for (auto& value : *this)
      {
        value = 1;
      }
    }

    ~Container()
    {
      delete [] buffer;
    }

  private:
    uint8_t * buffer;
    size_t size;
};

int main()
{
  int i = 2;
  double d = 1.6;

  std::cout << mul(i, d) << std::endl;
  std::cout << mul(d, i) << std::endl;


  Container objects(6);

  // let's store some values in container
  std::cout << "Attempt 1"  << std::endl;

  int counter = 0;
  for (auto obj : objects)
  {
    obj = ++counter;
  }

  // then realize that we updated copies
  for (auto obj : objects)
  {
    // static_cast just to prevent printing as char
    std::cout << static_cast<int>(obj) << std::endl;
  }

  // so this time let's do it correct
  std::cout << "Attempt 2"  << std::endl;

  counter = 0;
  for (auto& obj : objects)
  {
    obj = ++counter;
  }

  // here copy is ok since uint8_t is rather small
  for (auto obj : objects)
  {
    std::cout << static_cast<int>(obj) << std::endl;
  }

  return 0;
}
