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
#define STEP 2

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

void return_type_spec()
{
  int i1 = 2;
  int i2 = 3;
  int i3 = 0;

  i3 = add(i1, i2);
}
#endif // STEP == 1


#if STEP == 2

template <typename RET, typename T, typename U>
RET add(T t, U u)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;

  return t + u;
}

void return_type_as_param()
{
  int i1 = 2;
  float f1 = 1.1f;

  std::cout << "return_type_as_param() " << add<float>(i1, f1) << std::endl;
}

#endif // STEP == 2

int main()
{
#if STEP == 0
  ambiguous_call_ret_diff();
#endif // STEP == 0

#if STEP == 1
  return_type_spec();
#endif // STEP == 1

#if STEP == 2
  return_type_as_param();
#endif // STEP == 2

  return 0;
}

