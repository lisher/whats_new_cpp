/*
 *
 * What's new in C++
 * variadic - variadic template
 *
 * (c) Lisher
 *
 * Bonus: How much can be mix usage with and without units?
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

    // simple function that allows to add specified number of meters
    // to the distance
    void add(double distance)
    {
      std::cout << "Function " << __PRETTY_FUNCTION__ << " called for value='" << distance << "'" <<  std::endl;

      this->distance += distance;
    }

    void add(std::initializer_list<double> distances)
    {
      for (auto distance : distances)
      {
        this->distance += distance;
      }
    }

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

    template<typename VALUE, typename UNIT, typename... Rest>
    void add(VALUE value, UNIT unit, Rest... rest)
    {
      std::cout << "Function " << __PRETTY_FUNCTION__ << " called for value='" << value
                << "', unit='" << enum2str(unit) << "' and Rest" << std::endl;
      add(value, unit);
      add(rest...);
    }

    template<typename VALUE, typename... Rest>
    void add(VALUE value1, VALUE value2, Rest... rest)
    {
      std::cout << "Function " << __PRETTY_FUNCTION__ << std::endl
                << " called for value1='" << value1
                << "', with the following value2 = '" << value2 << "' and Rest" << std::endl;

      add(value1);
      add(value2, rest...);
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

  d1.add( {1.0, 2.3, 4.5, 2.2} );

  d1.log();

  d1.add(4.0, Distance::Unit::YARD);

  d1.log();

  d1.add(3.0, Distance::Unit::YARD, 8.0, Distance::Unit::METER, 1.2, Distance::Unit::YARD);

  d1.log();

  // This will work as we still have version of add that accepts single parameter
  d1.add(10.0, Distance::Unit::YARD, 1.0);

  d1.log();

  std::cout << std::endl;
  std::cout << "d1.add(10.0, 12.5, 11.0, Distance::Unit::YARD, 5.0, 3.0, Distance::Unit::METER, 11.0, 12.0);"
            << std::endl;

  d1.add(10.0, 12.5, 11.0, Distance::Unit::YARD, 5.0, 3.0, Distance::Unit::METER, 11.0, 12.0);

  d1.log();

  return 0;
}

