/*
 *
 * What's new in C++
 * variadic - variadic template
 *
 * (c) Lisher
 *
 * Simplest version. We need to add distances one at the time.
 */

#include <iostream>

// simple class that will store distance in meters
class Distance
{
  public:
    enum class Unit
    {
      METER,
      YARD
    };

    const char* enum2str(Unit unit)
    {
      switch (unit)
      {
        case Unit::METER:
          return "meter";
        case Unit::YARD:
          return "yard";
      }

      return "unsupported";
    }

  private:
    static constexpr const double YARD_TO_METER_RATION = 0.9144;

  public:
    Distance()
      : distance(0.0)
    {
    }

    // simple function that allows to add specified number of meters
    // to the distance
    void add(double distance)
    {
      this->distance += distance;
    }

    void log()
    {
      std::cout << "Current distance = " << distance << std::endl;
    }

  private:
    // in meters
    double distance;
};

int main()
{
  Distance d1;

  d1.log();

  d1.add(11.5);

  d1.log();

  return 0;
}

