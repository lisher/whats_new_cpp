/*
 *
 * What's new in C++
 * Type deduction - decomposition declaration (also called structured binding)
 *
 */

#include <iostream>
#include <set>

int main()
{
  // set stores sorted list of objects
  std::set<double> scores = { 12.9, 4.1, 6.2, 9.9, 10.0 };

  {
    std::cout << std::endl << "For pair" << std::endl << std::endl;

    // note that we don't need to provide variables declarations
    // before calling insert()
    auto [iter, success] = scores.insert(3.3);

    if (success)
    {
      std::cout << "Value 3.3 added to the set" << std::endl;

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
      std::cout << "Failed to insert value 3.3" << std::endl;
    }
  }
//------------------------------------------------------------------------------
  {
    std::cout << std::endl << "For array" << std::endl << std::endl;

    int points[] = { 1, 2, 3, 4 };

    auto [x, y, z, t] = points;

    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "z = " << z << std::endl;
    std::cout << "t = " << t << std::endl;
  }
//------------------------------------------------------------------------------
  {
    std::cout << std::endl << "For structure" << std::endl << std::endl;

    struct Call
    {
      std::string caller;
      std::string callee;
      std::string arguments;
    };

    Call listing = { "user", "ls", "-al" };

    auto & [who, what, how] = listing;

    std::cout << "Function called: " << what << " " << how << std::endl;
  }

  return 0;
}

