/*
 *
 * What's new in C++
 * variadic - variadic template
 *
 * (c) Lisher
 */

/*
 * STEP 0 - single argument function
 * STEP 1 - initializer_list
 * STEP 2 - value with unit
 * STEP 3 - variadic template
 * STEP 4 - invalid use of variadic template (*)
 * STEP 5 - ??
 */

#define STEP 0

#include <iostream>
#include <initializer_list>

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

#if STEP < 5
    // simple function that allows to add specified number of meters
    // to the distance
    void add(double distance)
    {
      this->distance += distance;
    }
#endif // STEP < 5

#if STEP >= 1
    void add(std::initializer_list<double> distances)
    {
      for (auto distance : distances)
      {
        this->distance += distance;
      }
    }
#endif // STEP >= 1

#if STEP >= 2
    void add(double distance, Unit unit)
    {
      switch (unit)
      {
        case Unit::METER:
          this->distance += distance;
          break;
        case Unit::YARD:
          this->distance += distance * YARD_TO_METER_RATION;
          break;
        default:
          // crash
          return;
      }
    }
#endif // STEP >= 2

#if STEP >=3

    template<typename VALUE, typename UNIT, typename... Rest>
    void add(VALUE value, UNIT unit, Rest... rest)
    {
      std::cout << "Function " << __PRETTY_FUNCTION__ << " called for value='" << value
                << "', unit='" << enum2str(unit) << "' and Rest" << std::endl;
      add(value, unit);
      add(rest...);
    }
#endif // STEP >= 3

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

#if STEP < 5
  d1.add(11.5);

  d1.log();
#endif // STEP < 5

#if STEP >= 1
  d1.add( {1.0, 2.3, 4.5, 2.2} );

  d1.log();
#endif // STEP >= 1

#if STEP >= 2
  d1.add(4.0, Distance::Unit::YARD);

  d1.log();
#endif // STEP >= 2

#if STEP >= 3
  d1.add(3.0, Distance::Unit::YARD, 8.0, Distance::Unit::METER, 1.2, Distance::Unit::YARD);

  d1.log();
#endif // STEP >= 3

#if STEP >= 4
  d1.add(3.0, Distance::Unit::YARD, 8.0, Distance::Unit::METER, 1.2);

  d1.log();
#endif // STEP >= 4


  return 0;
}

