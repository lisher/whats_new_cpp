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
    std::cout << *point << " ";
  }
  std::cout << std::endl;

  // better, we don't need to use container type nor stored entity type
  for (auto point = points.begin();
       point != points.end();
       ++point)
  {
    std::cout << *point << " ";
  }
  std::cout << std::endl;

  // now with range-based for loop
  // better, but we still need to use type of stored objects
  for (int point : points)
  {
    std::cout << point << " ";
  }
  std::cout << std::endl;

  // nice, now we only need to ensure that 'points' stores objects with
  // overloaded operator<< for output stream
  for (auto point : points)
  {
    std::cout << point << " ";
  }
  std::cout << std::endl;

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

// There is one difference between auto and template type deduction
void auto_init_list()
{
  auto a1 = 4;
  auto a2(4);

  std::cout << "a1 = " << a1 << " type = " << type(a1) << std::endl;
  std::cout << "a2 = " << a2 << " type = " << type(a2) << std::endl;

  // here initializer_list<int> will be deduced
  auto a3 = {4};
  auto a4{4};

  std::string a3_value;
  for (const auto & value : a3)
  {
    a3_value += std::to_string(value);
    a3_value += " ";
  }

  std::cout << "a3 = [" << a3_value << "] type = " << type(a3) << std::endl;
  std::cout << "a4 = " << a4 << " type = " << type(a4) << std::endl;

  auto a5 = {1, 2, 3};
  // wont compile
  // auto a6{1, 2, 3, 4};

  std::string a5_value;
  for (const auto & value : a5)
  {
    a5_value += std::to_string(value);
    a5_value += " ";
  }

  std::cout << "a5 = [" << a5_value << "] type = " << type(a5) << std::endl;

}

int main()
{
  for_each();

  with_new();

  auto_init_list();

  return 0;
}
