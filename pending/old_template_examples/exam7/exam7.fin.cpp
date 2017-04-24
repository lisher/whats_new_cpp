
// EXTD_CODE
// THIS CODE IS NOT PART OF THIS EXAMPLE
// USE ONLY TO ENABLE PRINTOUT

#define IO_FUN 1

#include <iostream>
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
 * Example 2
 * Template function with multiple arguments
 *
 */

class Coordinate
{
    public:
        Coordinate() : x(0), y(0), z(0) {}
        const Coordinate& operator=(const int& arg)
        {
            x = arg;
        }
        Coordinate(int x, int y, int z)
            : x(x), y(y), z(z)
        {}
        const Coordinate& operator+=(const Coordinate& rhs)
        {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            return *this;
        }
    public:
        int x;
        int y;
        int z;
};

std::ostream& operator<<(std::ostream& os, const Coordinate& rhs)
{
    os << rhs.x << rhs.y << rhs.z << std::endl;
    return os;
}

template <typename T>
class Adder
{
    public:
        Adder()
        {
            sum = 0;
        }

        T add(T value)
        {
            sum += value;
            return sum;
        }

        operator T()
        {
            return sum;
        }
    private:
        T sum;
};

int main()
{
    Adder<int> adder1;
    adder1.add(4);

    #ifdef IO_FUN
        std::cout << "Adder1 sum = " << adder1 << std::endl;
    #endif

    int i1 = 5;
    adder1.add(i1);

    #ifdef IO_FUN
        std::cout << "Adder1 sum = " << adder1 << std::endl;
    #endif

    Adder<Coordinate> adder2;
    adder2.add(Coordinate(1,2,3));

    #ifdef IO_FUN
        std::cout << "Adder2 sum = " << adder2 << std::endl;
    #endif

    return 0;
}
