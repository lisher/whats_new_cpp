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

#include <iostream>

class UdpConnection
{
};

class TcpConnection
{
};

class MySQLDatabase
{
};


class UniversalConnection
{
};

class DatabaseWrapper
{
};

// Small part of database with limited functionalities
class DatabaseCache
{
};

// used globally to not pass whole objects to other modules
class UniversalWrapper
{
  public:
    UniversalConnection wrap(UdpConnection udp)
    {
      UniversalConnection conn;

      // init universal interface to UDP Connection

      return conn;
    }
    UniversalConnection wrap(TcpConnection tcp)
    {
      UniversalConnection conn;

      // init universal interface to TCP Connection

      return conn;
    }
    DatabaseWrapper wrap(MySQLDatabase d)
    {
      DatabaseWrapper wrapper;

      // prepare queries for general access methods

      return wrapper;
    }
};

// used in modules where we don't have time to check
// the whole database
class DatabaseCompressor
{
  public:
    DatabaseCache wrap(MySQLDatabase d)
    {
      return DatabaseCache();
    }
};

template<typename T, typename U>
//decltype(t.wrap(u)) getWrapper(T t, U u)
decltype(std::declval<T>().wrap(std::declval<U>())) getWrapper(T t, U u)
//auto getWrapper(T t, U u) -> decltype(t.wrap(u))
{
  /*
  // This is a simple example, but let imagine
  // There is more to do here
  if (!t.active())
  {
    t.init()
    t.activate();
  }
  */

  return t.wrap(u);
}

int main()
{
  UniversalWrapper uw;
  DatabaseCompressor dc;

  UdpConnection udp;
  TcpConnection tcp;
  MySQLDatabase database;

  std::cout << type( getWrapper(uw, udp) ) << std::endl;
  std::cout << type( getWrapper(uw, tcp) ) << std::endl;
  std::cout << type( getWrapper(uw, database) ) << std::endl;
  std::cout << type( getWrapper(dc, database) ) << std::endl;

  return 0;
}
