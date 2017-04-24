
// EXTD_CODE
// THIS CODE IS NOT PART OF THIS EXAMPLE
// USE ONLY TO ENABLE PRINTOUT

#define IO_FUN 1

#include <iostream>
#include <sstream>
using namespace std;

#include <typeinfo>
#include <cxxabi.h>
#include <cstdlib>

const string demangle(const char* name) {

    int status = -4;

    char* res = abi::__cxa_demangle(name, NULL, NULL, &status);

    const char* const demangled_name = (status==0)?res:name;

    string ret_val(demangled_name);

    free(res);

    return ret_val;
}

// EXTD_CODE


/*
 * Example 3
 * Class template specialization
 *
 */

class A
{};
class B
{};
class C
{};

template <typename T = C>
class TurboHandler
{
    public:
        TurboHandler(T obj);
        int handle(T& obj)
        {
            return 1;
        }
        void swap(T& lhs, T& rhs)
        {
            T temp = lhs;
            lhs = rhs;
            rhs = temp;
        }
    private:
        T obj;
};

template <typename T>
TurboHandler<T>::TurboHandler(T obj)
{
    this->obj = obj;
}

template <>
class TurboHandler<A>
{
    public:
        TurboHandler(A& obj)
        {
            this->obj = obj;
        }
        int handle(A& obj)
        {
            return 2;
        }
        void swap(A& lhs, A& rhs)
        {
            // no swapping
        }
    private:
        A obj;
};

template <>
int TurboHandler<B>::handle(B& obj)
{
    return 3;
};

int main()
{
    A a1, a2;
    B b1, b2;
    C c1, c2;

    TurboHandler<A> ta(a2);
    TurboHandler<B> tb(b2);
    TurboHandler<> tc(c2);

    ta.handle(a1);
    tb.handle(b2);
    tc.handle(c2);

    ta.swap(a1, a2);
    tb.swap(b1, b2);
    tc.swap(c1, c2);

    #ifdef IO_FUN
        std::cout << ta.handle(a1) << std::endl;
        std::cout << tb.handle(b1) << std::endl;
        std::cout << tc.handle(c1) << std::endl;
    #endif
    return 0;
}
