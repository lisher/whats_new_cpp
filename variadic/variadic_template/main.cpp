/*******************************************************************************
 *
 * THIS IS NOT PART OF THIS EXAMPLE
 *
 *******************************************************************************/

#include <typeinfo>
#include <cxxabi.h>
#include <string>

const std::string demangle(const char* name)
{
    int status = -4;

    char* res = abi::__cxa_demangle(name, NULL, NULL, &status);

    const char* const demangled_name = (status==0)?res:name;

    std::string ret_val(demangled_name);

    free(res);

    return ret_val;
}

template <typename T>
const std::string type(T var)
{
    // resolved at compile time unless polymorphic type is used
    return demangle(typeid(var).name());
}

/*******************************************************************************
 *
 * BACK TO EXAMPLE
 *
 *******************************************************************************/

/*
 * STEP 0 - templates, reminder
 * STEP 1 - variadic template with small problem
 * STEP 2 - added missing stop point
 * STEP 3 - alternative stop point
 */

#define STEP 3

#include <iostream>

template <typename T>
void print(T arg)
{
    std::cout << "print(T) type='" << type(arg) << "' value='" << arg << "'" << std::endl;
}

#if STEP == 2

template <typename First>
void vtPrint(First first)
{
    std::cout << "vtPrint(F) type='" << type(first) << "' value='" << first << "'" << std::endl;
}

#endif

#if STEP >= 3

void vtPrint()
{
    std::cout << "vtPrint()" << std::endl;
}

#endif

#if STEP >= 1

template <typename First, typename... Rest>
void vtPrint(First first, Rest... rest)
{
    std::cout << "vtPrint(F,R) type='" << type(first) << "' value='" << first << "'" << std::endl;
    vtPrint(rest...);
}

#endif


int main()
{
    int number = 4;
    char sign = '+';

    print(number);
    print(sign);

#if STEP >= 1

    std::cout << std::endl << "Test vtPrint" << std::endl << std::endl;

    vtPrint(number, sign);
    vtPrint(number, sign, "cstring", -12.0);

#endif

    return 0;
}

