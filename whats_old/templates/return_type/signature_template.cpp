/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Return type and templates
 *
 */

// STEP 0 - ambiguous call when only return type is different
// STEP 1 - specialization for only return type
// STEP 2 - two base templates with different return type
// STEP 3 - return type as template parameter
#define STEP 0

#include <iostream>

#if STEP == 0

template <typename T, typename U>
T add (T t, U u)
{
  return t + u;
}

template <typename T, typename U>
U add (T t, U u)
{
  return t + u;
}

// Return type is not considered here, both base templates
// could be used in this case
void ambiguous_call_ret_diff()
{
  int i1 = 2;
  float f1 = 1.1f;

  add(i1, f1);
}

#endif // STEP == 0

#if STEP == 1

template <typename T>
T add(T t1, T t2)
{
  return t1 + t2;
}

template <typename T>
int add(T t1, T t2)
{
  return t1 + t2;
}

// Same as above, the fact that we store result in int
// is not enough to choose second base template
void return_type_spec()
{
  int i1 = 2;
  int i2 = 3;
  int i3 = 0;

  i3 = add(i1, i2);
}
#endif // STEP == 1


#if STEP == 2

// Here we have two base templates with different return type
template <typename T>
int add(T t1, T t2)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  return t1 + t2;
}

template <typename T>
float add(T t1, T t2)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  return t1 + t2;
}

void better_return_type_spec()
{
  int i1 = 3;
  int i2 = 4;

  // This line is incorrect
  // Compilete is unable to determine which base template is better
  //
  // int i3 = add(i1, i2);

  // Return type is part of function type so we can get a pointer
  // to correct, instantiated version of first template
  typedef int (*Func)(int, int);

  Func my_func = &add;

  std::cout << "my_func(1.0f, 2.5f) = " << my_func(1.0f, 2.5f) << std::endl;
}

#endif // STEP == 2


#if STEP == 3

template <typename RET, typename T, typename U>
RET add(T t, U u)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  return t + u;
}

template <typename T, typename U>
short add(T t, U u)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  return t + u;
}

void return_type_as_param()
{
  int i1 = 2;
  float f1 = 1.1f;

  std::cout << "add<float>(i1, f1) " << add<float>(i1, f1) << std::endl;

  // Here is a fun bit, compiler will choose second template
  // since it is unable to determine RET parameter type in
  // the first template
  std::cout << "add(i1, f1) " << add(i1, f1) << std::endl;
}

#endif // STEP == 3

int main()
{
#if STEP == 0
  ambiguous_call_ret_diff();
#endif // STEP == 0

#if STEP == 1
  return_type_spec();
#endif // STEP == 1

#if STEP == 2
  better_return_type_spec();
#endif // STEP == 2

#if STEP == 3
  return_type_as_param();
#endif // STEP == 3

  return 0;
}

