/*
 *
 * What's new in C++
 * Type deduction - decomposition declaration (also called structured binding)
 *
 * Using std::tie instead of decomposition declaration
 *
 */

#include <iostream>

#include <set>
#include <tuple>

int main()
{
  // set stores sorted list of objects
  std::set<double> scores = { 12.9, 4.1, 6.2, 9.9, 10.0 };

//------------------------------------------------------------------------------
  {
    // returns iterator to the inserted element and flag indicating
    // that insertion was successful (duplicates are not allowed)
    std::pair<std::set<double>::const_iterator, bool> res = scores.insert(7.7);

    if (res.second)
    {
      std::cout << "Value 7.7 added to the set" << std::endl;

      // let's print set content starting from inserted value
      std::set<double>::const_iterator iter = res.first;
      while (iter != scores.end())
      {
        std::cout << *iter << " ";
        ++iter;
      }
      std::cout << std::endl;
    }
    else
    {
      std::cout << "Failed to insert value 7.7" << std::endl;
    }

    std::cout << std::endl;
  }
//------------------------------------------------------------------------------
  {
    // attempt to insert element that is already in the set should fail
    std::pair<std::set<double>::const_iterator, bool> res = scores.insert(4.1);

    if (res.second)
    {
      std::cout << "Value 4.1 added to the set" << std::endl;

      // let's print set content starting from inserted value
      std::set<double>::const_iterator iter = res.first;
      while (iter != scores.end())
      {
        std::cout << *iter << " ";
        ++iter;
      }
      std::cout << std::endl;
    }
    else
    {
      std::cout << "Failed to insert value 4.1" << std::endl;
    }

    std::cout << std::endl;
  }
//------------------------------------------------------------------------------
  {
    // using auto reduce some typing, but we still have the pair to play with
    auto res = scores.insert(5.9);

    if (res.second)
    {
      std::cout << "Value 5.9 added to the set" << std::endl;

      // let's print set content starting from inserted value
      auto iter = res.first;
      while (iter != scores.end())
      {
        std::cout << *iter << " ";
        ++iter;
      }
      std::cout << std::endl;
    }
    else
    {
      std::cout << "Failed to insert value 5.9" << std::endl;
    }

    std::cout << std::endl;
  }
//------------------------------------------------------------------------------
  {
    bool success = false;
    std::set<double>::const_iterator iter;

    // we can use tie to bind results to separate variables
    // please note that unsell compiler optimaze this code
    // pair will still exists before its content is copied to
    // provided variables
    std::tie(iter, success) = scores.insert(1.1);

    if (success)
    {
      std::cout << "Value 1.1 added to the set" << std::endl;

      // let's print set content starting from inserted value
      while (iter != scores.end())
      {
        std::cout << *iter << " ";
        ++iter;
      }
      std::cout << std::endl;
    }
    else
    {
      std::cout << "Failed to insert value 1.1" << std::endl;
    }

    std::cout << std::endl;
  }

  return 0;
}

