/*
 *
 * What's new in C++
 * variadic - variadic template
 *
 */

// STEP 0 - for build-in type
// STEP 1 - for classes
// STEP 2 - for template
#define STEP 2
#include <iostream>

template <typename T>
class Stats
{
  public:
    static size_t noOfCreated;
    static size_t noOfObjects;

    template <typename... Args>
    static T * create(Args... args)
    {
      ++noOfCreated;
      ++noOfObjects;

      T * obj = new T(args...);
      return obj;
    }

    static void destroy(T *& obj)
    {
      --noOfObjects;

      delete obj;
      obj = nullptr;
    }
};

template <typename T>
size_t Stats<T>::noOfObjects = 0;

template <typename T>
size_t Stats<T>::noOfCreated = 0;

#if STEP >= 1
class Person
{
  public:
    Person()
      : name(""), address(""), age(0)
    {
    }
    Person(std::string name, std::string address, unsigned char age)
      : name(name), address(address), age(age)
    {
    }
  private:
    std::string name;
    std::string address;
    unsigned char age;
};
#endif // STEP >= 1

#if STEP == 2

template <typename T>
class NamedBuffer
{
  public:
    NamedBuffer(std::string name, size_t size, T defaultValue)
      : name(name),
        size(size)
    {
      buffer = new T[size];

      for (size_t i = 0 ; i < size ; ++i)
      {
        buffer[i] = defaultValue;
      }
    }

    ~NamedBuffer()
    {
      delete [] buffer;
    }

  private:
    std::string name;
    size_t size;

    T * buffer;
};

#endif // STEP == 2

int main()
{

#if STEP == 0

  int * p_int1 = Stats<int>::create(4);
  int * p_int2 = Stats<int>::create(100);

  std::cout << "No of ints (existing/created) = " << Stats<int>::noOfObjects << std::endl;

  Stats<int>::destroy(p_int1);
  Stats<int>::destroy(p_int2);

#endif // STEP == 0

#if STEP == 1

  Person * john = Stats<Person>::create("John Doe", "Dublin", 20);
  Person * mike = Stats<Person>::create("Mike Smith", "London", 33);

  std::cout << "No of persons (existing/created) = "
            << Stats<Person>::noOfObjects
            << "/"
            << Stats<Person>::noOfCreated
            << std::endl;

  Stats<Person>::destroy(mike);

  std::cout << "No of persons (existing/created) = "
            << Stats<Person>::noOfObjects
            << "/"
            << Stats<Person>::noOfCreated
            << std::endl;

  Stats<Person>::destroy(john);

  std::cout << "No of persons (existing/created) = "
            << Stats<Person>::noOfObjects
            << "/"
            << Stats<Person>::noOfCreated
            << std::endl;

#endif // STEP == 1

#if STEP == 2
  NamedBuffer<Person> * my_phonebook =
    Stats<NamedBuffer<Person>>::create("phonebook", 10, Person("unknown", "unknown", 0));

  std::cout << "No of person buffer (existing/created) = "
            << Stats<NamedBuffer<Person>>::noOfObjects
            << "/"
            << Stats<NamedBuffer<Person>>::noOfCreated
            << std::endl;

  NamedBuffer<float> * my_score =
    Stats<NamedBuffer<float>>::create("score", 5, 10.0);

  std::cout << "No of float buffer (existing/created) = "
            << Stats<NamedBuffer<float>>::noOfObjects
            << "/"
            << Stats<NamedBuffer<float>>::noOfCreated
            << std::endl;

  Stats<NamedBuffer<float>>::destroy(my_score);

  Stats<NamedBuffer<Person>>::destroy(my_phonebook);
#endif // STEP == 2

  return 0;
}

