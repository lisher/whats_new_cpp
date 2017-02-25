/*
 *
 * What's new in C++
 * Uniform initialization
 *
 */

/*
 * STEP 0 - what we know about CTORs and operator=
 * STEP 1 - let's verify is that's true
 */
#define STEP 2

#include <iostream>

class Object
{
  public:
    Object()
    {
      this->i = new int(0);
      this->f = new float(0.0);
      this->c = new char('\0');

      std::cout << "Object::Object()" << std::endl;
    }
    Object(int i, float f, char c)
    {
      this->i = new int(i);
      this->f = new float(f);
      this->c = new char(c);

      std::cout << "Object::Object(int, float, char)" << std::endl;
    }

    Object(const Object& rhs)
    {
      this->i = new int(*rhs.i);
      this->f = new float(*rhs.f);
      this->c = new char(*rhs.c);

      std::cout << "Object::Object(const Object&)" << std::endl;
    }
    const Object& operator=(const Object& rhs)
    {
      i = rhs.i;
      f = rhs.f;
      c = rhs.c;

      std::cout << "Object::operator=(const Object&)" << std::endl;

      return *this;
    }
#if STEP >= 1
    bool operator==(const Object& rhs)
    {
      return *i == *rhs.i && *f == *rhs.f && *c == *rhs.c;
    }
#endif // STEP >= 1

    int getI() const
    {
      return *i;
    }
    float getF() const
    {
      return *f;
    }
    char getC() const
    {
      return *c;
    }
  private:
    int* i;
    float* f;
    char* c;
};

#if STEP == 2

void print(Object o)
{
  std::cout << "i = " << o.getI()
            << " f = " << o.getF()
            << " c = " << o.getC()
            << std::endl;
}

#endif // STEP == 2

int main()
{
  Object o1(0, 0.0, '\0');
  Object o2(o1);
  Object o3;
  Object o4 = o3;
  o3 = o4;

  std::cout << "So now everything is "
            << ((o1 == o2 && o2 == o3 && o3 == o4) ? "true" : "false") << std::endl;

#if STEP == 2
  std::cout << std::endl << "Now let's check uniform initialization notation" << std::endl << std::endl;

  Object u1 {};
  Object u2 {1, 1.1, '1'};
  Object u3  = {3, 3.3, '3'};

  // when uniform initialization is shorter?

  std::cout << std::endl << "When function is called" << std::endl << std::endl;

  print(Object(2, 2.2, '2'));
  print({2, 2.2, '2'});
#endif // STEP == 2

  return 0;
}
