/*
 *
 * C++ after C++98
 *
 * Created: 11.08.2016
 * (c) lisher
 *
 */

#include <iostream>
#include <vector>

#define STEP 0

struct Employee
{
  std::string name;
  int id;
  int age;
  float salary;
};

class Book
{
  public:
    Book(int id, int pages, char index)
      : id(id), pages(pages), index(index)
    {}

    int getId() { return id; }
    int getPages() { return pages; }
    char getIndex() { return index; }
  private:
    int id;
    int pages;
    char index;
};

int main()
{
  // initializer list for structs
  Employee john = {"John Doe", 100, 28, 1200.0};
  Employee simon{"Simon Lane", 101, 30, 2700.0};

#if STEP == 1
  // doesn't work without defined CTOR
  Employee mark(std::string("Mark Smith"), 99, 20, 1400.0);
#endif

  std::cout << "name: " << john.name
    << " id: " << john.id
    << " age: " << john.age
    << " salary: " << john.salary
    << std::endl;

  // initializer list for c arrays

  int teamEagle[5] = {10, 20, 30, 40, 50};

  std::cout << "Team Eagle members: ";
  for (int i = 0 ; i < 5 ; ++i)
  {
    std::cout << teamEagle[i] << " ";
  }
  std::cout << std::endl;

  int teamFalcon[] = {11, 22, 33, 44, 55};

  std::cout << "Team Falcon members: ";
  for (int i = 0 ; i < 5 ; ++i)
  {
    std::cout << teamFalcon[i] << " ";
  }
  std::cout << std::endl;

  // initializer list for classes not supported in c++03
  Book got = {17, 800, 'c'};

  std::cout << "Book Game Of Thrones id " << got.getId()
    << " pages " << got.getPages()
    << " index " << got.getIndex()
    << std::endl;

  // but here the initializer_list comes into play
  std::vector<int> vArray = {3, 2, 7, 5, 8};

  std::cout << "vArray: ";
  for (int i = 0 ; i < 5 ; ++i)
  {
    std::cout << vArray[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
