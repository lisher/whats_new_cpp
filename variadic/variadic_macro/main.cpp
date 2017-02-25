/*
 *
 * What's new in C++
 * Variadic macro
 *
 */

/*
 * STEP 0 - macros intro
 * STEP 1 - variadic macro
 */
#define STEP 1

#include <iostream>

class Logger
{
  public:
    enum class Type
    {
      INFO,
      WARNING,
      ERROR
    };

    static void log(Type type, std::string msg)
    {
      switch (type)
      {
        case Type::INFO:
          std::cout << "[INFO]";
          break;
        case Type::WARNING:
          std::cout << "[WARN]";
          break;
        case Type::ERROR:
          std::cout << "[ERRO]";
          break;
      }
      std::cout << msg << std::endl;
    }
};

#define INFO(msg) Logger::log(Logger::Type::INFO, msg)

#if STEP == 1

#define CHECK(condition, ...) if (!(condition)) { printf(__VA_ARGS__); }

#endif // STEP == 1

int main()
{
  // wo can use long form
  Logger::log(Logger::Type::INFO, "All is ok");
  Logger::log(Logger::Type::ERROR, "Until it breaks");

  // or short form
  INFO("All is good again");

#if STEP == 1
  CHECK(true, "True is %s", "true");

  int size = 2;
  int limit = 1;

  CHECK(size < limit, "Size of container (%d) is bigger then limit (%d)\n", size, limit);

#endif // STEP == 1

  return 0;
}
