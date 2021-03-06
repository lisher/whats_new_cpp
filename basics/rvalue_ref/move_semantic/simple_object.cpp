/*
 *
 * What's new in C++
 * rvalue_refs - move semantic
 *
 */

#include <iostream>

// small macro that adds pretty printing before and after expression execution
#define CALL(EXP) std::cout << "#" << std::endl << "# BEFORE CALL " #EXP << std::endl << "#" << std::endl; \
  EXP; \
  std::cout << "#" << std::endl << "# AFTER CALL " #EXP << std::endl << "#" << std::endl;

class Buffer
{
  public:
    Buffer(unsigned int ownerId, size_t bufferSize)
      : ownerId(ownerId),
        bufferSize(bufferSize)
    {
      buffer = new int[bufferSize];

      std::cout << "      >> [" << myId << "][O=" << ownerId << "][S=" << bufferSize
                << "] Buffer::Buffer()" << std::endl;
    }

    Buffer(const Buffer & rhs)
      : ownerId(rhs.ownerId),
        bufferSize(rhs.bufferSize)
    {
      buffer = new int[bufferSize];

      std::cout << "      >> [" << myId << "][O=" << ownerId << "][S=" << bufferSize
                << "] Buffer::Buffer(const Buffer &)" << std::endl;
    }

    ~Buffer()
    {
      delete [] buffer;

      std::cout << "      >> [" << myId << "][O=" << ownerId << "][S=" << bufferSize
                << "] Buffer::~Buffer()" << std::endl;
    }

    Buffer & operator=(const Buffer & rhs)
    {
      delete [] buffer;

      ownerId = rhs.ownerId;
      bufferSize = rhs.bufferSize;
      buffer = new int[bufferSize];

      std::cout << "      >> [" << myId << "][O=" << ownerId << "][S=" << bufferSize
                << "] Buffer::operator=(const Buffer &)" << std::endl;

      return *this;
    }

    size_t size() const
    {
      return bufferSize;
    }

    static unsigned int getId()
    {
      return id;
    }

  private:
    static unsigned int id;
    unsigned int myId = ++id;

    unsigned int ownerId;
    int * buffer;
    size_t bufferSize;

    friend std::ostream & operator<<(std::ostream & stream, Buffer & buffer);
};

unsigned int Buffer::id = 0;

std::ostream & operator<<(std::ostream & stream, Buffer & buffer)
{
  return stream << "Buffer={id=" << buffer.myId
                << ", ownerId=" << buffer.ownerId
                << ", bufferSize=" << buffer.bufferSize
                << ", buffer=" << buffer.buffer
                << "}";
}

class SimpleObject
{
  public:
    SimpleObject(size_t value)
      : value(value)
    {
      std::cout << "    > [" << myId << "][V=" << value << "] SimpleObject::SimpleObject()" << std::endl;

      buffer = new Buffer(myId, value);
    }

    SimpleObject(const SimpleObject & rhs)
      : value(rhs.value)
    {
      std::cout << "    > [" << myId << "][V=" << value << "] SimpleObject::SimpleObject(const SimpleObject &)" << std::endl;

      buffer = new Buffer(*rhs.buffer);
    }

    ~SimpleObject()
    {
      std::cout << "    > [" << myId << "][V=" << value << "] SimpleObject::~SimpleObject()" << std::endl;

      delete buffer;
    }

    SimpleObject & operator=(const SimpleObject & rhs)
    {
      value = rhs.value;

      delete buffer;
      buffer = new Buffer(*rhs.buffer);

      std::cout << "    > [" << myId << "][V=" << value << "] SimpleObject::operator=(const Onject &)" << std::endl;

      return *this;
    }

    unsigned int getMyId() const
    {
      return myId;
    }

    static unsigned int getId()
    {
      return id;
    }

  private:
    static unsigned int id;
    unsigned int myId = ++id;

    size_t value;

    Buffer * buffer;

    friend std::ostream & operator<<(std::ostream & stream, SimpleObject & so);
};

unsigned int SimpleObject::id = 0;


std::ostream & operator<<(std::ostream & stream, SimpleObject & so)
{
  return stream << "SimpleObject={id=" << so.myId << ", value=" << so.value << ", buffer=" << *so.buffer << "}";
}

template <typename T>
void swap(T & a, T & b)
{
  T temp = a;
  a = b;
  b = temp;
}

void simple_object()
{
  SimpleObject so1 {10};
  SimpleObject so2 {20};

  std::cout << std::endl << "Created objects = " << SimpleObject::getId() << std::endl;
  std::cout << "Created buffers = " << Buffer::getId() << std::endl << std::endl;
  std::cout << "so1 = " << so1 << std::endl;
  std::cout << "so2 = " << so2 << std::endl;
  std::cout << std::endl;


  CALL( swap(so1, so2); );


  std::cout << std::endl << "Created objects = " << SimpleObject::getId() << std::endl;
  std::cout << "Created buffers = " << Buffer::getId() << std::endl << std::endl;
  std::cout << "so1 = " << so1 << std::endl;
  std::cout << "so2 = " << so2 << std::endl;
  std::cout << std::endl;
}

int main()
{
  simple_object();

  return 0;
}
