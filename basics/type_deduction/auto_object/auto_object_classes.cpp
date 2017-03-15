/*
 *
 * What's new in C++
 * Type deduction - auto
 *
 */

/*******************************************************************************
 *
 * THIS IS NOT PART OF THIS EXAMPLE
 *
 *******************************************************************************/

#include <typeinfo>
#include <cxxabi.h>
#include <string>

const std::string demangle(const char* name)
{
    int status = -4;

    char* res = abi::__cxa_demangle(name, NULL, NULL, &status);

    const char* const demangled_name = (status==0)?res:name;

    std::string ret_val(demangled_name);

    free(res);

    return ret_val;
}

template <typename T>
const std::string type(T var)
{
    // resolved at compile time unless polymorphic type is used
    return demangle(typeid(var).name());
}

/*******************************************************************************
 *
 * BACK TO EXAMPLE
 *
 *******************************************************************************/

// EXAMPLE 4 - auto member object
#define EXAMPLE 0

#include <vector>
#include <iostream>

// Example 1
// Using auto in loops
void for_each()
{
  std::cout << "Example 1 - auto + loops" << std::endl;

  std::vector<int> points {10, 20, 30, 40, 50};

  // task - printing container content

  // let's start with longest version
  // we need to use container type as well as type of objects stored in it
  for (std::vector<int>::iterator point = points.begin();
       point != points.end();
       ++point)
  {
    std::cout << *point << std::endl;
  }

  // now with range-based for loop
  // better, but we still need to use type of stored objects
  for (int point : points)
  {
    std::cout << point << std::endl;
  }

  // nice, now we only need to ensure that 'points' stores objects with
  // overloaded operator<< for output stream
  for (auto point : points)
  {
    std::cout << point << std::endl;
  }

}

// Example 2
// Using auto when creating object
void with_new()
{
  std::cout << "Example 2 - auto + new" << std::endl;

  // task - create complex object on heap

  // Ok, but we need to use type name two times
  std::vector<double>* ptr = new std::vector<double>();

  std::cout << type(ptr) << std::endl;

  delete ptr;


  auto ptr2 = new std::vector<double>();

  std::cout << type(ptr2) << std::endl;

  delete ptr2;
}

// Example 3
// Using auto when object type in irrelevent

// Library Alpha and Library Beta don't know about each other
// They know about data sets defined in Library Gamma
// We need to forward output from Library Alpha to Library Beta

class LibraryGammaDataSet
{
};

LibraryGammaDataSet libAlphaGetDataSet()
{
  return LibraryGammaDataSet();
}

void libBetaExtrapolation(LibraryGammaDataSet input)
{
  // do sth
}

#if EXAMPLE == 4
class Auto
{
  auto noOfWheels = 4;
  int noOfDoors = 2;
};
#endif // EXAMPLE == 4

void type_irrelevent()
{
  // Initialize Library Alpha
  // Run Library Alpha data generators

  // get data from Library A module
  auto data = libAlphaGetDataSet();

  // Initializa Library Beta
  // Connect Library Beta to network interface

  // forward collected data to Library Beta

  libBetaExtrapolation(data);
}

// Example 4
// Class member declared using auto

class Object
{
  public:
    // compilation error, member can be declared
    // using auto only if it is a static member
    // auto member = 1;

    // compilation error
    // in-class initialization is allowed only for _const_ statics
    //static auto member = 1;

    // compilation error
    // auto requires initialization
    //static auto member;

    static const auto member = 1;
};

int main()
{
  for_each();

  with_new();

  type_irrelevent();

  return 0;
}
