#include <iostream>
#include <iomanip>
#include <vector>

#include "IOScopeGuard.hpp"

namespace kovtun
{
  struct DataStruct
  {
    DataStruct():
      a(0)
    {}

    DataStruct(int _a):
      a(_a)
    {}

    int getValue() const
    {
      return a;
    }

  private:
    int a;
  };

  struct DelimiterI
  {
    char expected;
  };

  std::istream & operator>> (std::istream & in, DelimiterI && delimiter)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }

    char c = 0;
    in >> c;
    if (c != delimiter.expected)
    {
      in.setstate(std::ios::failbit);
    }

    return in;
  }

  std::istream & operator>> (std::istream & in, DataStruct & dataStruct)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    kovtun::IOScopeGuard scopeGuard(in);

    using del = DelimiterI;
    int a = 0;
    in >> del{'['} >> a >> del{']'};
    if (in)
    {
      dataStruct = DataStruct(a);
    }

    return in;
  }

  std::ostream & operator<< (std::ostream & out, const DataStruct & dataStruct)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    kovtun::IOScopeGuard ioScopeGuard(out);

    out << dataStruct.getValue() << " " << std::fixed << std::setprecision(1) << 123.456f;

    return out;
  }
}

int main()
{
  std::vector< kovtun::DataStruct > data;

  while (!std::cin.eof())
  {
    using input_it_t = std::istream_iterator< kovtun::DataStruct >;
    std::copy(input_it_t {std::cin},input_it_t {},std::back_inserter(data));

    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  using output_it_t = std::ostream_iterator< kovtun::DataStruct >;
  std::copy(data.cbegin(),data.cend(),output_it_t(std::cout, "\n"));

  return 0;
}

