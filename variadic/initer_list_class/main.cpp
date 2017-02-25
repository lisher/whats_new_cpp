#include <initializer_list>

#include <iostream>
#include <vector>

// First, it works for function

double average(std::initializer_list<double> args)
{
    double sum = 0.0;

    for (auto iter = args.begin(); iter != args.end(); ++iter)
    {
        sum += *iter;
    }

    return sum / args.size();
}

// Second, class

class Sampler
{
    public:
        Sampler(std::initializer_list<int> synchroPoints)
            : leader(1), base(10)
        {
            for (auto iter : synchroPoints)
            {
                this->synchroPoints.push_back(iter); // iter is int btw
            }
        }

        Sampler(int leader, std::initializer_list<int> synchroPoints)
            : leader(leader), base(10)
        {
            for (auto iter : synchroPoints)
            {
                this->synchroPoints.push_back(leader * iter);
            }
        }

        // and since std::vector has constructor(initializer_list)
        Sampler(int leader, int base, std::initializer_list<int> synchroPoints)
            : leader(leader), base(base), synchroPoints(synchroPoints)
        {
        }

        void log()
        {
            std::cout << "Sampler, leader = " << leader
                      << " base = " << base
                      << " synchro values ";
            for (auto iter : synchroPoints)
            {
                std::cout << iter << " ";
            }
            std::cout << std::endl;
        }

    private:
        int leader;
        int base;
        std::vector<int> synchroPoints;
};

int main()
{

    std::cout << average({1, 2, 3, 4, 5}) << std::endl;
    std::cout << average({1, 2, 3, 4}) << std::endl;

    Sampler lowPrecisionSampler({1, 2});
    Sampler mediumPrecisionSampler(3, {1, 2, 3, 5, 8, 13});
    Sampler highPrecisionSampler(1, 16, {1, 2, 4, 8, 16, 32, 64});

    lowPrecisionSampler.log();
    mediumPrecisionSampler.log();
    highPrecisionSampler.log();

    return 0;
}

