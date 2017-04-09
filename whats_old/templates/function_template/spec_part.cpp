/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Example 4
 * More complex specialization
 *
 */

#include <iostream>
#include <cctype>

template<typename T>
bool equal(T a, T b)
{
  std::cout << __PRETTY_FUNCTION__ << " (" << a << ", " << b << ")" << std::endl;

  return a == b;
}

// let's start with just one template
void test_single_template()
{
  // we know that this works
  int i1 = 2;
  int i2 = 2;

  std::cout << "i1 = " << i1 << " i2 = " << i2
            << " equal = " << equal(i1, i2)
            << std::endl;

  // here template will compare pointers, not data under them
  int * ptr_i1 = &i1;
  int * ptr_i2 = &i2;

  std::cout << "ptr_i1 = " << ptr_i1 << " ptr_i2 = " << ptr_i2
            << " equal = " << equal(ptr_i1, ptr_i2)
            << std::endl;
}


// Note: this is a new base template overloading previous template
//       not a partial specialization (which are forbidden for
//       functions)
template <typename T>
bool equal(T * a, T * b)
{
  std::cout << __PRETTY_FUNCTION__ << " (" << a << ", " << b << ")"
            << " *(" << *a << ", " << *b << ")"
            << std::endl;

  return *a == *b;
}

void test_pointer_spec()
{
  // second version of template better matches used arguments
  int i1 = 2;
  int i2 = 2;

  int * ptr_i1 = &i1;
  int * ptr_i2 = &i2;

  std::cout << "*ptr_i1 = " << *ptr_i1 << " *ptr_i2 = " << *ptr_i2
            << " equal = " << equal(ptr_i1, ptr_i2)
            << std::endl;
}


// full specialization of
//
// template<typename T>
// bool equal(T a, T b)
//
template<>
bool equal(unsigned int a, unsigned int b)
{
  std::cout << "Specialized " << __PRETTY_FUNCTION__ << " (" << a << ", " << b << ")" << std::endl;

  return (a % 10) == (b % 10);
}

// full specialization of
//
// template<typename T>
// bool equal(T * a, T * b)
//
template<>
bool equal(unsigned int * a, unsigned int * b)
{
  std::cout << "Specialized " << __PRETTY_FUNCTION__ << " (" << a << ", " << b << ")"
            << " *(" << *a << ", " << *b << ")"
            << std::endl;

  return (*a % 10) == (*b % 10);
}

void test_full_specialization()
{
  unsigned int ui1 = 902;
  unsigned int ui2 = 10002;

  std::cout << "ui1 = " << ui1 << " ui2 = " << ui2
            << " equal = " << equal(ui1, ui2)
            << std::endl;

  unsigned int * ptr_ui1 = &ui1;
  unsigned int * ptr_ui2 = &ui2;

  std::cout << "*ptr_ui1 = " << *ptr_ui1 << " *ptr_ui2 = " << *ptr_ui2
            << " equal = " << equal(ptr_ui1, ptr_ui2)
            << std::endl;
}


int main()
{
  test_single_template();

  test_pointer_spec();

  test_full_specialization();

  return 0;
}
