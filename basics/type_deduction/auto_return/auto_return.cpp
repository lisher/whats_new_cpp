/*
 *
 * What's new in C++
 * Type deduction - auto return type
 * (c) Lisher
 *
 */

#include <iostream>

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

        bool operator!=(const iterator& rhs) const
        {
          return ptr != rhs.ptr;
        }

        // instead "iterator& operator++()"
        auto& operator++()
        {
          ++ptr;

          return *this;
        }

        // instead "uint8_t& operator*()"
        // Note that auto without & would be resolved to uint8_t
        auto& operator*()
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

    // begin() and end() need to be placed before ctor
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

      for (auto value = begin();
           value != end();
           ++value)
      {
        *value = 1;
      }

      // We could also use range-based for
      // Note that value is no longer a pointer
      //
      // for (auto & value : *this)
      // {
      //   value = 1;
      // }
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

  for (auto& obj : objects)
  {
    std::cout << static_cast<int>(obj) << std::endl;
  }

  return 0;
}
