/*
 *
 * What's new in C++
 * Type deduction - decomposition declaration (also called structured binding)
 *
 * Using std::tie instead of decomposition declaration
 *
 */

#include <set>
#include <iostream>

int main()
{
  // set stores sorted list of objects
  std::set<double> scores = { 4.1, 6.2, 9.9, 10.0 };

  std::pair<std::set<double>::const_iterator, bool> res = scores.insert(7.7);

  if (res.second)
  {
    std::set<double>::iterator iter = res.first;
    while (iter != scores.end())
    {
      std::cout << *iter << " ";
      ++iter;
    }
    std::cout << std::endl;
  }

  //TODO
  // 1 - apply auto
  // 2 - version with tie
  // 3 - in separate file version with decomposition decl
  //
  // ?? maybe split this into legacy and tie?

  return 0;
}

