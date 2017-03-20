/*
 *
 * What's new in C++
 * Type deduction - decltype(auto)
 *
 */

// STEP 0 - operator returning auto
// STEP 1 - operator returning decltype(auto)
#define STEP 1

#include <iostream>
#include <bitset>

class Mask
{
  public:
    Mask(unsigned char bits, std::string name = "anonymous")
      : bits(bits),
        name(name)
    {
    }

    void log()
    {
      std::cout << "Mask '" << name << "' contains " << std::bitset<8>(bits) << std::endl;
    }

  private:
    unsigned char bits;
    std::string name;

#if STEP == 0
    friend auto operator|=(Mask& lhs, const Mask& rhs);
#endif // STEP == 0

#if STEP == 1
    friend decltype(auto) operator|=(Mask& lhs, const Mask& rhs);
#endif // STEP == 1
};

#if STEP == 0
// this will not even compile
auto operator|=(Mask& lhs, const Mask& rhs)
{
  lhs.bits |= rhs.bits;

  return lhs;
}
#endif // STEP == 0

#if STEP == 1
decltype(auto) operator|=(Mask& lhs, const Mask& rhs)
{
  lhs.bits |= rhs.bits;

  return lhs;
}
#endif // STEP == 1

void test_safe()
{
  // note C++14 introduces binary literals
  Mask m1{0b11000000, "m1"};
  Mask m2{0b00110000, "m2"};
  Mask m3{0b00001100, "m3"};
  Mask m4{0b00000011, "m4"};

  m1.log();
  m2.log();
  m3.log();
  m4.log();
  std::cout << std::endl;

  // note that bracket are needed since operator |= is right to left
  // the following line will modify m3, then m2, then m1
  // m1 |= m2 |= m3 |= m4;

  // Please node that we only want to modify m1
  ((m1 |= m2) |= m3) |= m4;

  m1.log();
  m2.log();
  m3.log();
  m4.log();
  std::cout << std::endl;
}

int main()
{
  test_safe();

  return 0;
}
