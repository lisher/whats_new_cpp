/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Template parameter interface - sortable
 *
 */

// STEP 0 - sorting of Points
// STEP 1 - sorting of ints
#define STEP 0

#include <cstddef>
#include <iostream>

template <typename T, size_t S>
void sort(T (&array)[S])
{
  for (size_t i = 0 ; i < S ; ++i)
  {
    for (size_t j = 0 ; j < S ; ++j)
    {
      if (array[i].compare(array[j]) < 0)
      {
        T temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }
}

class Point
{
  public:
    int compare(const Point & point)
    {
      return (x + y > point.x + point.y) ? 1 :
               (x + y == point.x + point.y ? 0 : -1);
    }

    Point()
      : x(0.0f), y(0.0f)
    {}
    Point(float x, float y)
      : x(x), y(y)
    {}

  private:
    float x;
    float y;

    friend std::ostream & operator<<(std::ostream & stream, const Point & point);
};

std::ostream & operator<<(std::ostream & stream, const Point & point)
{
  return stream << "(" << point.x << ", " << point.y << ")";
}

int main()
{
  Point points[4];

  Point a(10, 10);
  Point b(5, 5);
  Point c(2, 2);
  Point d(1, 1);

  points[0] = a;
  points[1] = b;
  points[2] = c;
  points[3] = d;

  std::cout << "Before sort" << std::endl;

  for (int i = 0 ; i < 4 ; ++i)
  {
    std::cout << points[i] << std::endl;
  }

  sort(points);

  std::cout << "After sort" << std::endl;

  for (int i = 0 ; i < 4 ; ++i)
  {
    std::cout << points[i] << std::endl;
  }

#if STEP == 1
  int ints[5] = {5, 4, 3, 2, 1};

  sort(ints);
#endif // STEP == 1

  return 0;
}
