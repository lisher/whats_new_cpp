/*
 *
 * What's new in C++
 * rvalue_refs - basics
 *
 */

#include <iostream>

// STEP 0 - code without errors
// STEP 1 - seg fault on access to reference to deleted object
// STEP 2 - same seg fault for const reference
// STEP 3 - another seg fault when we try to hijack local variable
#define STEP 0

// small macro that adds pretty printing before and after expression execution
#define CALL(EXP) std::cout << "#" << std::endl << "# BEFORE CALL " #EXP << std::endl << "#" << std::endl; \
  EXP; \
  std::cout << "#" << std::endl << "# AFTER CALL " #EXP << std::endl << "#" << std::endl;

class Buffer
{
  public:
    Buffer(unsigned int ownerId)
      : ownerId(ownerId),
        buffer(nullptr),
        bufferSize(0)
    {
    }
    ~Buffer()
    {
      delete [] buffer;
    }

    void initBuffer(size_t bufferSize)
    {
      std::cout << "    >> [O#" << ownerId << "] Buffer - Initializing" << std::endl;
      this->bufferSize = bufferSize;
      buffer = new int[bufferSize];
    }

    void releaseBuffer()
    {
      std::cout << "    >> [O#" << ownerId << "] Buffer - Releasing" << std::endl;
      bufferSize = 0;
      delete [] buffer;
      buffer = nullptr;
    }

    size_t size() const
    {
      return bufferSize;
    }

  private:
    unsigned int ownerId;
    int * buffer;
    size_t bufferSize;

    // int* data1;
    // int* data2;
    // (...)
};

class Object
{
  public:
    Object()
    {
      std::cout << "    > [" << myId << "] Object::Object()" << std::endl;
      buffer.initBuffer(1);
    }
    Object(size_t bufferSize)
    {
      buffer.initBuffer(bufferSize);
    }
    Object(const Object & rhs)
    {
      std::cout << "    > [" << myId << "] Object::Object(const Object &)" << std::endl;

      buffer.initBuffer(rhs.buffer.size());
    }
    ~Object()
    {
      std::cout << "    > [" << myId << "] Object::~Object()" << std::endl;

      buffer.releaseBuffer();
    }

    Object & operator=(const Object & rhs)
    {
      std::cout << "    > [" << myId << "] Object::operator=(const Onject &)" << std::endl;

      buffer.releaseBuffer();
      buffer.initBuffer(rhs.buffer.size());

      return *this;
    }

    unsigned int getId() const
    {
      return myId;
    }

  private:
    static unsigned int id;
    unsigned int myId = id++;

    Buffer buffer { myId };

};

unsigned int Object::id = 1;


// Different ways of creating objects using ctor and copy assignment
void step1()
{
  std::cout << "Step 1" << std::endl;

  // Create object
  CALL( Object obj1; );
  CALL( Object obj2 = obj2; );

  CALL( Object obj3; );
  CALL( obj3 = obj2; );

  std::cout << "#" << std::endl << "# END OF SCOPE" << std::endl << "#" << std::endl;
}


// Objects passed to/returned from functions

void getByValue(Object obj)
{
  // do sth
}

Object returnByValue()
{
  Object obj;
  return obj;
}

void step2()
{
  std::cout << std::endl << "Step 2" << std::endl << std::endl;

  // Now let call some functions

  CALL( Object obj4; );

  // will create one additional copy
  CALL( getByValue(obj4) );

  // if we explicit ask compiler to perform no optimization
  // will create two additional copies (one local object and one returned object)
  // otherwise will create just one object
  CALL( Object obj8 = returnByValue(); );

  std::cout << "#" << std::endl << "# END OF SCOPE" << std::endl << "#" << std::endl;
}


// Objects + functions + references

void getByRef(Object& obj)
{
  // do sth
}

// GCC will print
// warning: reference to local variable ‘obj’ returned [-Wreturn-local-addr]
Object& returnByRef()
{
  Object obj;
  return obj;
}

void step3()
{
  std::cout << std::endl << "Step 2" << std::endl << std::endl;

  CALL( Object obj9; );

  CALL( getByRef(obj9); );

#if STEP == 1

  // will cause segmentation fault when copy ctor tires to
  // get size of rhs buffer
  CALL( Object obj10 = returnByRef() );

#endif //STEP == 1


  std::cout << "#" << std::endl << "# END OF SCOPE" << std::endl << "#" << std::endl;
}


// Object + functions + const reference

void getByConstRef(const Object& obj)
{
  // do sth
}

// GCC will print
// warning: reference to local variable ‘obj’ returned [-Wreturn-local-addr]
const Object& returnByConstRef()
{
  Object obj;
  return obj;
}

const Object& pass(const Object & obj)
{
  return obj;
}

void step4()
{
  std::cout << std::endl << "Step 2" << std::endl << std::endl;

  CALL( Object obj11; );

  CALL( getByConstRef(obj11); );

#if STEP == 2

  // will cause segmentation fault when copy ctor tires to
  // get size of rhs buffer
  CALL( Object obj12 = returnByConstRef() );

#endif // STEP == 2

  // Wait, but I heard that const reference can extend lifetime of object!
  //
  // Sure it can, but I don't see any reference above that could do it.

#if STEP == 3

  CALL( const Object & obj13 = returnByConstRef() );

  // segmentation fault
  // Why? Because it extend object lifetime in case of temporaries returned
  // by function. Local variables have to be deleted at the end of scope.
  std::cout << "obj13.getId() = " <<  obj13.getId() << std::endl;

#endif // STEP == 3

  // Ok now let's do it correct

  CALL( const Object & obj14 = returnByValue() );

  std::cout << "obj14.getId() = " <<  obj14.getId() << std::endl;

  // We can throw this object here and there
  CALL( const Object & obj15 = pass(obj14); );

  std::cout << "#" << std::endl << "# END OF SCOPE" << std::endl << "#" << std::endl;
}
int main()
{
  // Simple cases with copy ctor and copy assignment
  step1();
  // Objects passed to/returned from functions
  step2();
  // Objects + functions + references
  step3();
  // Objects + functions + const references (extended lifetime)
  step4();

  return 0;
}
