/*
 *
 * What's new in C++
 * Uniform initialization
 *
 */

class Point
{
  public:
    Point()
      : x(256), y(256)
    {}
    Point(int x, int y)
      : x(x), y(y)
    {}
  private:
    unsigned int x;
    unsigned int y;
};

class Rectangle
{
  public:
    Rectangle(Point a, Point b)
      : a(a), b(b)
    {}

  private:
    Point a;
    Point b;
};

int main()
{
  // FIXME this is not a problem :P
  Rectangle(Point(), Point());
  return 0;
}
