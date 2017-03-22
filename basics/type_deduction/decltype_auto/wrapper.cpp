/*
 *
 * What's new in C++
 * Type deduction - decltype(auto)
 *
 */

// STEP 0 - explicit types in Buffer
// STEP 1 - returning auto in BUffer
// STEP 2 - returning decltype(auto) in BUffer
// STEP 3 - decltype(auto) with wrapper to at()
#define STEP 3

#include <iostream>
#include <cstring>


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

    void resize(size_t newSize)
    {
      uint8_t* newData = new uint8_t[newSize];
      memcpy(newData, data, size);
      delete [] data;
      data = newData;
      size = newSize;
    }
    void log()
    {
      std::cout << "Buffer size = " << size << std::endl;
      for (size_t i = 0 ; i < size ; ++i)
      {
        std::cout << "[" << i << "] = " << +data[i] << std::endl;
      }
    }

#if STEP == 0 || STEP == 3
    uint8_t at(size_t index) const
    {
      return data[index];
    }

    uint8_t& operator[](size_t index)
    {
      return data[index];
    }
#endif // STEP == 0 || STEP == 3

#if STEP == 1
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
#endif // STEP == 1

#if STEP == 2
    // changing it to decltype(auto) wont change anything
    // as deta[x] is not a reference
    decltype(auto) at(size_t index)
    {
      return data[index];
    }

    decltype(auto) operator[](size_t index)
    {
      return data[index];
    }
#endif // STEP == 2

  private:
    uint8_t * data;
    size_t size;
};


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

#if STEP == 3
    static decltype(auto) safer_access(Buffer & buffer, size_t index)
    {
      if (index > buffer.getSize())
      {
        buffer.resize(index + 1);
      }
      return buffer.at(index);
    }
#endif // STPE == 3
};

int main()
{
  Buffer shelf(3);

  shelf[0] = 13;
  shelf[1] = 14;

  shelf.log();

  Wrapper::safe_access(shelf, 5) = 99;

  shelf.log();

#if STEP == 3
  Wrapper::safer_access(shelf, 7) = 77;

  shelf.log();
#endif // STEP == 3

  return 0;
}

