/*
 *
 * What's new in C++
 * Type deduction - declval
 *
 */

#include <cstdint>
#include <list>
#include <iostream>

#define CHECK_TYPE(VAR, TYPE) std::cout << (std::is_same<decltype(VAR), TYPE>::value ? #VAR " is " #TYPE : #VAR " isn't " #TYPE) << std::endl
#define NL std::cout << std::endl

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

    static int anotherFunc()
    {
      std::cout << "anotherFunc() call" << std::endl;
      return 0;
    }

};

void addition();

int main()
{
  // OK, but class name need to be used
  std::list<SyncPacket> input1;
  CHECK_TYPE(input1, std::list<SyncPacket>);
  NL;

  std::list<decltype(&SyncIpConnection::getNextPacket)> input2;
  CHECK_TYPE(input2, std::list<SyncPacket>);
  CHECK_TYPE(input2, std::list<SyncPacket (SyncIpConnection::*)()>);
  NL;

  std::list<decltype(std::declval<SyncIpConnection>().getNextPacket())> input3;
  CHECK_TYPE(input3, std::list<SyncPacket>);
  NL;

  // same effect may be achived using pointers (note that reference need to
  // by initizalized), but require variable initialization
  SyncIpConnection * ptr;
  std::list<decltype(ptr->getNextPacket())> input4;
  CHECK_TYPE(input4, std::list<SyncPacket>);
  NL;

  addition();

  return 0;
}


void addition()
{

  // Small break, why do we need an '&' in example above?

  // getNextPacket is not a static invalid use of non-static function
//  std::list<decltype(SyncIpConnection::getNextPacket)> input3;

  CHECK_TYPE(SyncIpConnection::anotherFunc, int (*)());
//  type_check(SyncIpConnection::anotherFunc);

  // Compare with typical pointer to member example
  typedef SyncPacket (SyncIpConnection::*mem_func)();
  mem_func ptr = &SyncIpConnection::getNextPacket;

  typedef int (*mem_func2)();
  mem_func2 ptr2 = &SyncIpConnection::anotherFunc;
  mem_func2 ptr3 = SyncIpConnection::anotherFunc;

  // Standard say's:
  // A pointer to member is only formed when an explicit & is used and
  // its operand is a qualiﬁed-id not enclosed in parentheses.
}
