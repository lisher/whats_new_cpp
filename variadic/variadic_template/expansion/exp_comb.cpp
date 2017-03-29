/*
 *
 * What's new in C++
 * variadic - variadic template
 *
 */

#include <iostream>

auto sum()
{
  return 0;
}

template <typename Head, typename... Rest>
auto sum(Head head, Rest... rest)
{
  std::cout << "Function " << __PRETTY_FUNCTION__
            << " called for head ='" << head
            << "' and the rest" << std::endl;

  return head + sum(rest...);
}

template <typename... Rest>
auto simple(Rest... rest)
{
  // Expands to E1, E2, E3, ...
  return sum(rest...);
}

template <typename... Rest>
auto one_more(Rest... rest)
{
  std::cout << "Function " << __PRETTY_FUNCTION__
            << " called" << std::endl;

  // expands to ++E1, ++E2, ++E3, ...
  return sum(++rest...);
}

template <typename... Rest>
auto double_it(Rest... rest)
{
  std::cout << "Function " << __PRETTY_FUNCTION__
            << " called" << std::endl;

  // expands to E1 * 2, E2 * 2, E3 * 2, ...
  return sum((rest * 2)...);
}

template <typename... Rest>
auto square(Rest... rest)
{
  std::cout << "Function " << __PRETTY_FUNCTION__
            << " called" << std::endl;

  // expands to E1 * E1, E2 * E2, E3 * E3, ...
  return sum((rest * rest)...);
}

template <typename... Rest>
auto call_function(Rest... rest)
{
  std::cout << "Function " << __PRETTY_FUNCTION__
            << " called" << std::endl;

  // expands to abs(E1), abs(E2), abs(E3) ...
  return sum(abs(rest)...);
}

template <typename... Rest>
auto sum_in_sum(Rest... rest)
{
  std::cout << "Function " << __PRETTY_FUNCTION__
            << " called" << std::endl;

  // expands to sum(E1, E2, E3, ...) + E1, sum(E1, E2, E3, ...) + E2, ...
  return sum(sum(rest...) + rest...);
}

int main()
{
  std::cout << "simple = " <<  simple(1, 2, 3.1, 4, 5) << std::endl;

  std::cout << "one_more = " <<  one_more(1, 2, 3.1, 4, 5) << std::endl;

  std::cout << "double_it = " <<  double_it(1, 2, 3.1, 4, 5) << std::endl;

  std::cout << "square = " <<  square(1, 2, 3.1, 4, 5) << std::endl;

  std::cout << "sum_in_sum = " <<  sum_in_sum(1, 2, 3.1, 4, 5) << std::endl;

  std::cout << "call_function = " <<  call_function(-1, 2, -3.1, 4, -5) << std::endl;

  return 0;
}

