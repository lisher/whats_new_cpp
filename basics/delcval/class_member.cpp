#include <cstdint>
#include <list>
#include <iostream>

// Function used to check argument type.
// Since it doesn't have definition compiler will protest
// with pretty printout.
template <typename T>
void type_check(T);

struct SyncPacket
{
  unsigned int refId;
  unsigned int seqNo;
  uint8_t data[80];
};


class SyncIpConnection
{
  public:
    // CTOR with multiple arguments,
    // each connection reserves port, adds itself to a pool ...
    // SyncIpConnection(args);

    SyncPacket getNextPacket()
    {
      SyncPacket example;

      return example;
    }
/*
    static int anotherFunc()
    {
      std::cout << "anotherFunc() call" << std::endl;
      return 0;
    }
*/
};

int main()
{
  // OK, but class name need to be used
  std::list<SyncPacket> input1;
//  type_check(input1);

  std::list<decltype(&SyncIpConnection::getNextPacket)> input2;
//  type_check(input2);

  std::list<decltype(std::declval<SyncIpConnection>().getNextPacket())> input3;
//  type_check(input3);

  return 0;
}


void addition()
{
  /*
  // Small break, why do we need an '&' in example above?
//  std::list<decltype(SyncIpConnection::getNextPacket)> input3;
  type_check(SyncIpConnection::anotherFunc);

  // Compare with typical pointer to member example
  typedef SyncPacket (SyncIpConnection::*mem_func)();
  mem_func ptr = &SyncIpConnection::getNextPacket;

  typedef int (*mem_func2)();
  mem_func2 ptr2 = SyncIpConnection::anotherFunc;
*/
}
