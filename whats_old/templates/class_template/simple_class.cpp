/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Class template
 *
 */

// STEP 0 - correct examples
// STEP 1 - type deduction before C++17
// STEP 2 - verify that type is correctly checked
#define STEP 2

// Adding any library makes generated files
// more difficult to analyze
#define IO_ENABLED 1

#if IO_ENABLED != 0

#include <iostream>

#endif // IO_ENABLED


template <typename T>
class Lock
{
  public:
    Lock(T value = T())
      : value(value),
        locked(false)
    {
    }

    T get() const
    {
      return value;
    }

    bool set(T value)
    {
      if (locked)
      {
        return false;
      }
      else
      {
        this->value = value;
        return true;
      }
    }

    void lock()
    {
      locked = true;
    }

    void unlock()
    {
      locked = false;
    }

  private:
    T value;
    bool locked;
};

void correct_examples()
{
  Lock<int> noOfThreads(10);

  noOfThreads.lock();

  noOfThreads.set(5);
#if IO_ENABLED != 0
  std::cout << "Number of threads = " << noOfThreads.get() << std::endl;
#endif // IO_ENABLED

  noOfThreads.unlock();

  noOfThreads.set(5);
#if IO_ENABLED != 0
  std::cout << "Number of threads = " << noOfThreads.get() << std::endl;
#endif // IO_ENABLED


  Lock<char> index('A');
  index.unlock();

#if IO_ENABLED != 0
  Lock<std::string> owner("Mark");

  owner.lock();

  owner.set("Bob");
  std::cout << "Owner = " << owner.get() << std::endl;
#endif // IO_ENABLED
}

class Object
{};

void incorrect_examples()
{
#if STEP == 1
  // type deduction for class templates not possible
  // until C++17
  Lock ratio(2.3);

#endif // STEP == 1

#if STEP == 2
  Lock<Object> size;

  size.set(10.0);
#endif // STEP == 2
}

int main()
{
  correct_examples();

  incorrect_examples();

  return 0;
}
