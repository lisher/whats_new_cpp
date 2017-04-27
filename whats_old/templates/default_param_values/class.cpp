/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Default values of template parameter - classes
 *
 */

#include <iostream>
#include <algorithm>

template <typename T, typename Compare = std::less<T>>
class SortedContainer
{
  private:
    struct Node
    {
      Node* next;
      T value;
    };

  public:
    SortedContainer()
      : head(NULL),
        size(0)
    {}

    void add(T arg)
    {
      // Please note that less is a type
      Compare compare;

      Node * node = new Node;
      node->value = arg;
      node->next = NULL;

      if (head == NULL)
      {
        head = node;
      }
      else if (compare(arg, head->value))
      {
        node->next = head;
        head = node;
      }
      else
      {
        Node * current = head;
        while (current->next != NULL)
        {
          if (compare(arg, current->next->value))
          {
            node->next = current->next;
            current->next = node;

            return;
          }
          current = current->next;
        }

        current->next = node;
      }
    }

    size_t getSize()
    {
      return size;
    }

    class iterator
    {
      public:
        iterator()
          : ptr(NULL)
        {
        }

        iterator & operator++()
        {
          ptr = ptr->next;

          return *this;
        }

        T & operator*()
        {
          return ptr->value;
        }

        bool operator!=(const iterator & rhs)
        {
          return ptr != rhs.ptr;
        }

      private:
        iterator(Node * node)
        {
          ptr = node;
        }

        Node * ptr;

        friend SortedContainer;
    };

    iterator begin()
    {
      return iterator(head);
    }
    iterator end()
    {
      return iterator(NULL);
    }

  private:
    Node * head;
    size_t size;
};


template <typename T>
struct my_greater
{
  bool operator()(const T & lhs, const T & rhs)
  {
    return std::abs(lhs) > std::abs(rhs);
  }
};

int main()
{
  // using default template argument for Compare
  SortedContainer<int> score;

  score.add(4);
  score.add(10);
  score.add(7);

  std::cout << "Score" << std::endl;
  for (SortedContainer<int>::iterator iter = score.begin();
       iter != score.end();
       ++iter)
  {
    std::cout << *iter << " " << std::endl;
  }

  SortedContainer<float, my_greater<float>> temperature;

  temperature.add(-0.5f);
  temperature.add(2.2f);
  temperature.add(4.2f);
  temperature.add(-10.0f);

  std::cout << "Temperature" << std::endl;
  for (SortedContainer<float, my_greater<float>>::iterator iter = temperature.begin();
       iter != temperature.end();
       ++iter)
  {
    std::cout << *iter << " " << std::endl;
  }
}
