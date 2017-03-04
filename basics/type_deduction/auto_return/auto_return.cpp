/*
 *
 * What's new in C++
 * Type deduction - auto
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
        interator()
          : obj(nullptr)
        {
        }
      private:
        uint8_t* obj;
    };
    Container()
      : buffer(nullptr)
    {
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

  return 0;
}
