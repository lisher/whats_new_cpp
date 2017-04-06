/*
 *
 * What's new in C++
 * Type deduction - new auto
 *
 */

#include <iostream>

#include <list>
#include <algorithm>
#include <utility>

////////////////////////////////////////////
// Allocators
////////////////////////////////////////////

// Class that implements stack on... stack
template <typename T, size_t SIZE>
class StackAllocator
{
  public:
    T * alloc()
    {
      if ((size_t)(latest - data) == SIZE)
      {
        return nullptr;
      }
      else
      {
        return latest++;
      }
    }

    bool free(T * data)
    {
      // if data == nullptr or
      // pointer points to object other last
      if (!data || data != latest - 1)
      {
        return false;
      }
      else
      {
        --latest;
        return false;
      }
    }

  private:
    T data[SIZE];
    T * latest = data;
};

template <typename T, size_t MAX>
class DynamicAllocator
{
  public:
    T* alloc()
    {
      if (inUse.size() == MAX)
      {
        return nullptr;
      }
      else
      {
        inUse.push_back(new T());
        return inUse.back();
      }
    }

    bool free(T * data)
    {
      if (!data)
      {
        return false;
      }

      for (auto iter = inUse.begin(); iter != inUse.end(); ++iter)
      {
        if (*iter == data)
        {
          delete *iter;
          inUse.erase(iter);
          return true;
        }
      }

      return false;
    }

    ~DynamicAllocator()
    {
      std::for_each(inUse.begin(), inUse.end(), [](T * data) { delete data; });
    }

  private:
    std::list<T*> inUse;
};


////////////////////////////////////////////
// Data classes
////////////////////////////////////////////

class Position
{
  public:
    Position()
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~Position()
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    void set(float x, float y, float z)
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }

    void log()
    {
      std::cout << "x = " << x << " y = " << y << " z = " << z << std::endl;
    }

  private:
    float x;
    float y;
    float z;
};

void test_stack_allocator()
{
  std::cout << std::endl << "Stack Allocator" << std::endl;

  StackAllocator<Position, 2> stack;

  Position * start = stack.alloc();
  start->set(0, 0, 0);
  start->log();

  Position * stop = stack.alloc();
  stop->set(1, 1, 1);
  stop->log();

  if (stack.alloc() == nullptr)
  {
    std::cout << "Unable to alloc more objects!" << std::endl;
  }

  stack.free(stop);

  Position * target = stack.alloc();
  target->set(10, 10, 10);
  target->log();


  // example for build-in types
  StackAllocator<int, 10> intStackAllocator;
  int * ptr = intStackAllocator.alloc();
  *ptr = 10;
}

void test_dynamic_allocator()
{
  std::cout << std::endl << "DynamicAllocator" << std::endl;

  DynamicAllocator<Position, 3> dynamic;

  Position * posA = dynamic.alloc();
  Position * posB = dynamic.alloc();
  Position * posC = dynamic.alloc();
  Position * posD = dynamic.alloc();

  if (posD == nullptr)
  {
    std::cout << "Dynamic allocation didn't allocate memory for posD" << std::endl;
  }
}

template <template<typename, size_t> typename Allocator, typename Object, size_t Size>
std::pair<Object*, Object*> alloc(Allocator<Object, Size> & allocator)
{
  std::pair<Object*, Object*> result;

  result.first = allocator.alloc();
  result.second = allocator.alloc();

  if (result.second == nullptr)
  {
    if (result.first == nullptr)
    {
      std::cout << "[WARNING] Unable to allocate any object in pair" << std::endl;
    }
    else
    {
      std::cout << "[WARNING] Unable to allocate second object in pair" << std::endl;

      allocator.free(result.first);
      result.first = nullptr;
    }
  }

  return result;
}

void test_creating_pairs()
{
  std::cout << std::endl << __FUNCTION__ << std::endl;

  StackAllocator<Position, 3> stackAlloc;
  DynamicAllocator<Position, 4> dynamicAlloc;

  auto pointA = alloc(stackAlloc);
  auto pointB = alloc(stackAlloc);

  auto pointC = alloc(dynamicAlloc);
  auto pointD = alloc(dynamicAlloc);
  auto pointE = alloc(dynamicAlloc);

}

//
// BONUS
// C++11 maked this example a little more dull
//

template <typename Allocator>
auto alloc_cpp11(Allocator & allocator)
{
  auto first = allocator.alloc();
  auto second = allocator.alloc();

  if (second == nullptr)
  {
    if (first == nullptr)
    {
      std::cout << "[WARNING] Unable to allocate any object in pair" << std::endl;
    }
    else
    {
      std::cout << "[WARNING] Unable to allocate second object in pair" << std::endl;

      allocator.free(first);
      first = nullptr;
    }
  }

  return std::make_pair(first, second);
}

void test_cpp11_creating_pairs()
{
  std::cout << std::endl << __FUNCTION__ << std::endl;

  StackAllocator<Position, 3> stackAlloc;
  DynamicAllocator<Position, 4> dynamicAlloc;

  auto pointA = alloc_cpp11(stackAlloc);
  auto pointB = alloc_cpp11(stackAlloc);

  auto pointC = alloc_cpp11(dynamicAlloc);
  auto pointD = alloc_cpp11(dynamicAlloc);
  auto pointE = alloc_cpp11(dynamicAlloc);
}

int main()
{
  test_stack_allocator();

  test_dynamic_allocator();

  test_creating_pairs();

  test_cpp11_creating_pairs();

  return 0;
}

