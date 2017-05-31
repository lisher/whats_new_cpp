/*
 *
 * What's new in C++
 * Type deduction - decltype(auto)
 *
 */

// NOTE:
// This example should be moved to section for move semantic

#include <iostream>
#include <cstring>

#define CHECK_TYPE(DECL, TYPE) std::cout << (std::is_same<DECL, TYPE>::value ? #DECL " == " #TYPE : #DECL " != " #TYPE) << std::endl
#define NL std::cout << std::endl

class Buffer
{
  public:
    Buffer(size_t size)
      : size(size)
    {
      data = new uint8_t[size];
      memset(data, 0, size);
    }
    ~Buffer()
    {
      delete [] data;
    }

    Buffer & operator=(const Buffer & rhs)
    {
      std::cout << "Called > " << __PRETTY_FUNCTION__ << std::endl;

      delete [] data;
      data = new uint8_t[rhs.size];
      size = rhs.size;
      memcpy(data, rhs.data, size);

      return *this;
    }
    Buffer & operator=(Buffer && rhs)
    {
      std::cout << "Called > " << __PRETTY_FUNCTION__ << std::endl;

      size = rhs.size;
      data = rhs.data;
      rhs.data = nullptr;

      return *this;
    }

    size_t getSize() const
    {
      return size;
    }

    void resize(size_t newSize)
    {
      uint8_t* newData = new uint8_t[newSize];
      memcpy(newData, data, size <= newSize ? size : newSize);
      delete [] data;
      data = newData;
      size = newSize;
    }
    void log()
    {
      std::cout << std::endl << "Buffer size = " << size << std::endl;

      for (size_t i = 0 ; i < size ; ++i)
      {
        std::cout << "[" << i << "] = " << +data[i] << std::endl;
      }

      std::cout << std::endl;
    }

    uint8_t at(size_t index) const
    {
      return data[index];
    }

    uint8_t& operator[](size_t index)
    {
      return data[index];
    }

  private:
    uint8_t * data;
    size_t size;
};

template <typename T>
decltype(auto) trim(T && buffer)
{
  std::cout << "Called > " << __PRETTY_FUNCTION__ << std::endl;

  size_t newSize = buffer.getSize();
  for (size_t i = buffer.getSize() - 1 ; i > 0  ; --i)
  {
    if (buffer[i] == 0)
    {
      --newSize;
    }
  }

  if (buffer.getSize() != newSize)
  {
    buffer.resize(newSize + 1);
  }
  CHECK_TYPE(decltype(std::forward<T>(buffer)), T);
  CHECK_TYPE(decltype(std::forward<T>(buffer)), T&);
  CHECK_TYPE(decltype(std::forward<T>(buffer)), T&&);

  return std::forward<T>(buffer);
}

int main()
{
  Buffer safe(10);
  safe[0] = 0;
  safe[1] = 1;
  safe[2] = 2;

  safe.log();

  trim(safe);

  safe.log();


  Buffer a(4);
  a[0] = 1;

  Buffer b(4);
  b[0] = 2;
  b[1] = 2;

  std::cout << "a" << std::endl;
  a.log();
  std::cout << "b" << std::endl;
  b.log();

  a = trim(b);

  std::cout << "a" << std::endl;
  a.log();
  std::cout << "b" << std::endl;
  b.log();

  a = trim(Buffer(100));

  std::cout << "a" << std::endl;
  a.log();

  return 0;
}
