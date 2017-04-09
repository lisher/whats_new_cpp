/*
 * What's old in C++
 * Templates
 * (c) Lisher
 *
 * Example 1
 * Function vs template function
 *
 */


// Adding any library makes generated files
// much harded to analyze
#define IO_ENABLED 0

#if IO_ENABLED != 0

#include <iostream>

#endif // IO_ENABLED


// Forward declaration are possible for templates
template<typename T>
T add(T lhs, T rhs);

template<typename T>
T add(T lhs, T rhs)
{
    #if IO_ENABLED != 0
        std::cout << __PRETTY_FUNCTION__ << " (" << lhs << ", " << rhs << ")" << std::endl;
    #endif

    return lhs + rhs;
}


float add(float lhs, float rhs)
{
    #if IO_ENABLED != 0
        std::cout << "add(" << lhs << ", " << rhs << ")" << std::endl;
    #endif

    return lhs + rhs;
}

int main()
{
    int i1 = 2;
    int i2 = 3;

    // uses template to generate add<int>
    int i3 = add(i1,i2);

    float f1 = 1.2;
    float f2 = 2.3;

    // uses plaind old function add(float, float)
    float f3 = add(f1,f2);

    // we can explicitly ask for template version
    float f4 = add<float>(f1,f2);

    return 0;
}
