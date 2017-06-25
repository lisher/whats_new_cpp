/*
 *
 * What's new in C++
 * variadic - variadic template
 *
 * (c) Lisher
 */

#include <iostream>

#define PFE_ENABLED 0
#define PRINT_FUNC_ENTER if (PFE_ENABLED) std::cout << __PRETTY_FUNCTION__ << std::endl

void printMenu()
{
  PRINT_FUNC_ENTER;

  // do nothing
}

// this could be more complex funtion from GUI that will also
// handle menu and call some user defined callback function when
// one option is selected
template <typename Head, typename... Rest>
void printMenu(Head head, Rest... rest)
{
  PRINT_FUNC_ENTER;

  std::cout << "[ ] " << head << std::endl;

  printMenu(rest...);
}

class Module
{
  public:
    Module(std::string name, double version)
      : name(name), version(version)
    {
    }

    std::string getTitle()
    {
      return name + " v" +  std::to_string(version);
    }
  private:
    std::string name;
    double version;
};

// Note that this function doesn't need stop condition as
// as no "recurence" is used
template <typename... Rest>
void printMenuByTitles(Rest... rest)
{
  PRINT_FUNC_ENTER;

  printMenu((rest.getTitle())...);
}

void function_call_on_param_pack()
{
  printMenu("Locator", "Database", "Network Config");

  std::cout << std::endl;

  Module sorter("Sorter", 1.2);
  Module converter("Hex Converter", 0.1);
  Module iterator("Random iterator", 2.0);

  printMenuByTitles(sorter, converter, iterator);

  // This will not compile as template function requires
  // that arguments have member function getTitle()
  //
  // printMenuByTitles(12, 11, 10);
}

int main()
{
  function_call_on_param_pack();

  return 0;
}

