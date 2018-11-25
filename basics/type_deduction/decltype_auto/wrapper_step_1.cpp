/*
 *
 * What's new in C++
 * Type deduction - decltype(auto)
 *
 * Purpose:
 * In this example we create class Buffer that represent table of bytes
 * allocated on heap. We want to support two methods of accessing
 * Buffer content, member function at() and operator[].
 * Function at() shouldn't allow to modify Buffer content.
 *
 * By changing returned type you can observe how interface of class changes.
 * Furhter down we create helper functions that use Buffer interface. Because
 * they also return decltype(auto) changes in Buffer interface propagate to
 * those functions.
 *
 * When using decltype(auto) remember that type deduction is very flexible.
 * It will automatically update all interfaces, so change in one function
 * may cause unexpected errors in different part of code.
 */

// STEP 1 - returning auto in BUffer

#include <iostream>
#include <cstring>


// Container that stores dynamic table of bytes
class Buffer
{
  public:
    Buffer(size_t size)
      : size(size)
    {
      data = new uint8_t[size];
    }
    ~Buffer()
    {
      delete [] data;
    }

    size_t getSize() const
    {
      return size;
    }

    // Changes the size of buffer
    void resize(size_t newSize)
    {
      uint8_t* newData = new uint8_t[newSize];

      if (newSize > size)
      {
        memcpy(newData, data, size);
      }
      else
      {
        // yes, we are loosing data here
        memcpy(newData, data, newSize);
      }

      delete [] data;
      data = newData;
      size = newSize;
    }
    void log()
    {
      std::cout << "Buffer size = " << size << std::endl;
      for (size_t i = 0 ; i < size ; ++i)
      {
        // plus added to convince cout to print as numbers and not as chars
        std::cout << "[" << i << "] = " << +data[i] << std::endl;
      }
    }

    // if we change return type to auto
    // both functions will return uint8_t
    auto at(size_t index)
    {
      return data[index];
    }

    auto operator[](size_t index)
    {
      return data[index];
    }

  private:
    uint8_t * data;
    size_t size;
};


// Note that Buffer has no check that prevent accessing elements
// from outside of its size. Let's create wrappers that will
// automatically change Buffer size.
class Wrapper
{
  public:
    static decltype(auto) safe_access(Buffer & buffer, size_t index)
    {
      if (index > buffer.getSize())
      {
        buffer.resize(index + 1);
      }
      return buffer[index];
    }
};

int main()
{
  Buffer shelf(3);

  shelf[0] = 13;
  shelf[1] = 14;

  shelf.log();

  Wrapper::safe_access(shelf, 5) = 99;

  shelf.log();

  return 0;
}

