#include <iostream>

namespace kovtun
{
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

    out << dataStruct.getValue();
    return out;
  }
}

int main()
{
  kovtun::DataStruct someData(0);

  if (!(std::cin >> someData))
  {
    std::cin.clear(); // порядок важен
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n'); // топаем до конца

    if (!(std::cin >> someData))
    {
      std::cerr << "бан" << "\n";
    }
  }

  std::cout << someData << "\n";

  return 0;
}

