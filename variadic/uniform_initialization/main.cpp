/*
 *
 * What's new in C++
 * Uniform initialization
 *
 */

#include <iostream>
#include <vector>

#include <initializer_list>

#define STEP 1

class Highlighter
{
    public:
        Highlighter(std::initializer_list<std::string> marks)
            : language("none"), precision(100), marks(marks)
        {
        }

        Highlighter(std::string language, int precision = 100)
            : language(language), precision(precision)
        {
        }

        void log()
        {
            std::cout << "Highlighter language = " << language
                      << " precision = " << precision
                      << " marks = ";

            for (auto iter : marks)
            {
                std::cout << "'" << iter << "' ";
            }
            std::cout << std::endl;
        }

    private:
        std::string language;
        int precision;
        std::vector<std::string> marks;
};

struct Card
{
    int id;
    char letter;
    double size;
};

int main()
{
    Card bCard {11, 'c', 2.3};
    std::cout << "bCard id = " << bCard.id
              << " letter = " << bCard.letter
              << " size = " << bCard.size
              << std::endl;

    Highlighter codingRules {"if(", "while(", "using namespace"};
    Highlighter polish {"polish", 80};

    codingRules.log();
    polish.log();

    std::vector<int> vec1 {1, 2, 3, 4};

    std::cout << "vec1 = ";
    for (auto iter : vec1)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

#if STEP >= 1
    {
        Highlighter signum {"emysign"};
        signum.log();

        {
            // when curved brackets are used CTOR(initializer_list<T>) takes precedence
            Highlighter swedish("swedish");
            swedish.log();


            // Note
            // vector with one element
            std::vector<int> vec2{8};

            // empty vector of size 8
            std::vector<int> vec3(8);
        }
    }
#endif

    return 0;
}

