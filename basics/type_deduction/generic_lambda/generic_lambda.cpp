/*
 *
 * What's new in C++
 * Type deduction - generic lambda
 *
 */

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

int main()
{
  std::vector<int> fib {1, 1, 2, 3, 5, 8, 13, 21, 34};

  std::for_each(fib.begin(), fib.end(), [] (int value) { std::cout << "(" << value << ") "; });
  std::cout << std::endl;

  std::list<std::string> os {"Mint", "Debian", "Fedora", "RedHat", "Ubuntu"};

  std::for_each(os.begin(), os.end(), [] (std::string value) { std::cout << "(" << value << ") "; });
  std::cout << std::endl;
  std::cout << std::endl;

  auto decorator = [] (const auto & value) { std::cout << "[" << value << "] "; };

  std::set<double> points {1.1, 2.2, 3.3, 4.4};

  std::for_each(points.begin(), points.end(), decorator);
  std::cout << std::endl;

  std::for_each(fib.begin(), fib.end(), decorator);
  std::cout << std::endl;

  std::for_each(os.begin(), os.end(), decorator);
  std::cout << std::endl;

  return 0;
}
