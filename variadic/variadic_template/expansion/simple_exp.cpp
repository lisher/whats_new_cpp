/*
 *
 * What's new in C++
 * variadic - variadic template
 *
 */

#include <iostream>

void printMenu()
{
  // do nothing
}

// this could be more complex funtion from GUI that will also
// handle menu and call some user defined callback function when
// one option is selected
template <typename Head, typename... Rest>
void printMenu(Head head, Rest... rest)
{
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

template <typename... Rest>
void printMenuByTitles(Rest... rest)
{
  printMenu(((rest).getTitle())...);
}

void function_call_on_param_pack()
{
  printMenu("Locator", "Database", "Network Config");

  Module sorter("Sorter", 1.2);
  Module converter("Hex Converter", 0.1);
  Module iterator("Random iterator", 2.0);

  printMenuByTitles(sorter, converter, iterator);
}

int main()
{
  function_call_on_param_pack();

  return 0;
}

