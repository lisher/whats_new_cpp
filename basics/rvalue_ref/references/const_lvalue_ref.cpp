/*
 *
 * What's new in C++
 * rvalue_refs - const lvalue references
 * (c) Lisher
 *
 */

#include <iostream>

// STEP 0 - extending lifetime of returned temporary
// STEP 1 - returning const reference to function local variable
// STEP 2 - same but with additional reference to const
// STEP 3 - reference const that is a member of object
// STEP 4 - passing rvalue to function that accepts reference to const
#define STEP 0

class A
{
  public:
    A(std::string name)
      : x(0), name(name)
    {
      std::cout << "["  << name << "] CTOR " <<  __PRETTY_FUNCTION__ << std::endl;

      ++created;
    }
    ~A()
    {
      std::cout << "["  << name << "] " << __PRETTY_FUNCTION__ << std::endl;
    }

    A(const A & rhs)
    {
      if (&rhs == NULL)
      {
        std::cout << "[????] CTOR " << __PRETTY_FUNCTION__ << " Attempt to copy from  &rhs == " << &rhs << std::endl;
      }
      else
      {
        x = rhs.x;

        name = std::string("copy of ") + rhs.name;

        std::cout << "["  << name << "] CTOR " << __PRETTY_FUNCTION__ << std::endl;
      }

      ++created;
    }

    A & operator++()
    {
      std::cout << "["  << name << "] " << __PRETTY_FUNCTION__ << std::endl;

      ++x;

      return *this;
    }

    A operator++(int) const
    {
      std::cout << "["  << name << "] " << __PRETTY_FUNCTION__ << std::endl;

      A temp("post-incr-temp");
      temp.x = x + 1;

      return temp;
    }

    A operator+(const A & rhs) const
    {
      std::cout << "["  << name << "] " << __PRETTY_FUNCTION__ << std::endl;

      A temp("add-temp");
      temp.x = x + rhs.x;

      return temp;
    }

    int getX() const
    {
      return x;
    }
    std::string getName() const
    {
      return name;
    }

  private:
    int x;
    std::string name;

  public:
    static int created;
};

int A::created = 0;



void test_return_temporary()
{
  std::cout << std::endl << __FUNCTION__ << std::endl;

  A a1("local a1");

  const A & cref = a1++;
  // if temporary produced as the result from a1++ was not bind to a reference to const
  // it would be destroyed at the end of above expression

  std::cout << "cref.x == " << cref.getX() << " a1.x == " << a1.getX() << std::endl;
}


const A & return_ref_to_local()
{
  A local("created-in-fun");

  return local;
}

// So can reference to const be used to extend lifetime of
// function local variable ?
void test_return_const_ref()
{
  std::cout << std::endl << __FUNCTION__ << std::endl;

  A a2 = return_ref_to_local();

  std::cout << "&a2 == " << &a2 << std::endl;
  std::cout << "a2.name == " << a2.getName() << " a2.x == " << a2.getX() << std::endl;
}

// Well maybe assigning it to second reference to const will help?
void test_return_const_ref_two()
{
  std::cout << std::endl << __FUNCTION__ << std::endl;

  const A & a3 = return_ref_to_local();

  std::cout << "&a3 == " << &a3 << std::endl;

  // just to be sure
  if (&a3)
  {
    std::cout << "a3.name == " << a3.getName() << " a3.x == " << a3.getX() << std::endl;
  }
}


// Now let's check if binding temporary to member
// will extend its lifetime
class Container
{
  public:
    Container(const A & value)
      : value(value)
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    const A & value;
};

void test_store_in_member_const_ref()
{
  std::cout << std::endl << __FUNCTION__ << std::endl;

  Container c1(return_ref_to_local());

  // now someone should ask what if we pass temporary that will exist while
  // constructor of Container is running

//  Container c1(A("local-in-test"));

//  A eraser("override-them-all");

  std::cout << "&c1.value == " << &c1.value << std::endl;

  // just to be sure
  if (&c1.value)
  {
    std::cout << "c1.value.name == " << c1.value.getName() << " c1.value.x == " << c1.value.getX() << std::endl;
  }
}


// Now let's check the ability of reference to const to bind rvalues
void describe_arg(const A & arg)
{
  std::cout << __FUNCTION__ << " received arg with name : " << arg.getName()
            << " and value : " << arg.getX() << std::endl;
}
void describe_arg_copy(A arg)
{
  std::cout << __FUNCTION__ << " received arg with name : " << arg.getName()
            << " and value : " << arg.getX() << std::endl;
}

void test_binding_to_rvalues()
{
  std::cout << std::endl << __FUNCTION__ << std::endl;

  A a4("a4");

  // lvalue passed as argument
  describe_arg(a4);

  std::cout << std::endl;

  // rvalue passed as argument
  describe_arg(a4++);

  std::cout << std::endl;

  // please not that lifetime of temporary doesn't need to be extended
  // as it exists until the end to full expression
  describe_arg_copy(a4++);
  // note that even through function works on copy of argument
  // temporary is destroyed at expression end
}

int main()
{
#if STEP == 0
  test_return_temporary();
#endif // STEP == 0

#if STEP == 1
  test_return_const_ref();
#endif // STEP == 1

#if STEP == 2
  test_return_const_ref_two();
#endif // STEP == 2

#if STEP == 3
  test_store_in_member_const_ref();
#endif // STEP == 3

#if STEP == 4
  test_binding_to_rvalues();
#endif // STEP == 4

  return 0;
}
