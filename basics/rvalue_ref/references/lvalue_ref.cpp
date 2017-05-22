/*
 *
 * What's new in C++
 * rvalue_refs - lvalue references
 *
 */

int get_three()
{
  return 3;
}

int bad_global = 1000;

int & get_bg()
{
  return bad_global;
}

int & pass_by_ref(int & arg)
{
  return ++arg;
}

class A {};
class B : public A {}

class C
{
  public:
    A & operator A() {
      return a;
    }

  private:
    A a;
}

int main()
{
  int x = 4;

  // creating reference the correct way i.e. initialized from lvalue
  int & ref = x;

  // now let's try to create reference to rvalue

  // from constant
  int & ref2 = 3;

  // from temporary returned by function
  int & ref3 = get_three();

  // from result of expression which is rvalue
  int & ref4 = x + 1;


  // please note that some expressions returns lvalues
  int & ref5 = ++x;

  // function get_bg returns lvalue
  int & ref6 = get_bg();

  // Same rules apply to function that takes parameter by reference
  pass_by_ref(x);

  // doesn't work for rvalue
  pass_by_ref(3);


  // implicit conversion is allowed for non-const lvalue ref (*)
  float & ref_f = x;

  // (*) with small exceptions
  B obj_b;
  C obj_c;

  // allowed as B deeived from A
  A & ref_a1 = obj_b;
  // allowed as C has convertion operator to A
  A & ref_a2 = obj_c;

  return 0;
}
