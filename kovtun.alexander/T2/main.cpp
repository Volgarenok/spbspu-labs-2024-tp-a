#include <iostream>
#include <iomanip>

namespace kovtun
{
  class ioScopeGuard
  {
  public:
    ioScopeGuard(std::basic_ios< char > & s) :
        s_(s),
        fill_(s.fill()),
        precision_(s.precision()),
        flags_(s.flags())
    {};

    ~ioScopeGuard()
    {
      s_.fill(fill_);
      s_.precision(precision_);
      s_.flags(flags_);
    };

  private:
    std::basic_ios< char > & s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };

  struct DataStruct
  {
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

  struct DelimiterIO
  {
    char expected;
  };

  std::istream & operator>> (std::istream & in, DelimiterIO && delimiter)
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

    using del = DelimiterIO;
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

    ioScopeGuard ioScopeGuard(out); // RAII example
    out << dataStruct.getValue() << std::fixed << std::setprecision(2) << 123.456f;

    return out;
  }
}

int main()
{
  kovtun::DataStruct someData(0);

  if (!(std::cin >> someData))
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');

    if (!(std::cin >> someData))
    {
      std::cerr << "бан" << "\n";
    }
  }

  std::cout << someData << "\n";

  return 0;
}

