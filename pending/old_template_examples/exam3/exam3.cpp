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

template <typename T>
class Bucket
{
    public:
        Bucket(T* element)
        {
            this->element = element;
        }

        const T* getElement() const
        {
            #ifdef IO_FUN
                std::cout << "Bucket<"
                    << demangle(typeid(T).name())
                    << ">::getElement" << std::endl;
            #endif
            return element;
        }
    private:
        T* element;
};

class Coordinate
{
    public:
        Coordinate(int x, int y, int z)
            : x(x), y(y), z(z)
        {}

        int x;
        int y;
        int z;
};

#ifdef IO_FUN
    std::ostream& operator<<(ostream& os, const Coordinate& co)
    {
        os << "(" << co.x << ", " << co.y << ", " << co.z << ")";
        return os;
    }
#endif

int main()
{
    int size = 10;
    float score = 19.6;
    Coordinate start(1, 1, 1);

    Bucket<int> buc_size(&size);
    Bucket<float> buc_score(&score);
    Bucket<Coordinate> buc_start(&start);

    #ifdef IO_FUN
        std::cout << *(buc_size.getElement()) << std::endl;
        std::cout << *(buc_score.getElement()) << std::endl;
        std::cout << *(buc_start.getElement()) << std::endl;
    #endif
    return 0;
}
