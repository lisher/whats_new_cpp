/*
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
*/

/*
 * Example 3
 * Class template
 *
 */

#include "Even.h"

int main()
{
    Even<int> e1(3);
    e1.getValue();

    #ifdef IO_FUN
        std::cout << e1.getValue() << std::endl;
    #endif
    return 0;
}
