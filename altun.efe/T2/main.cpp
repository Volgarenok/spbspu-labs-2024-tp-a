#include <iostream>
#include <string>
#include <ios>
#include <vector>
#include <limits>
#include <algorithm>
#include <iterator>
#include "streamGuard.hpp"

namespace altun
{

  struct Delimiter
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, Delimiter&& del)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    StreamGuard s_guard(in);
    char c = 0;
    in >> c;
    if (c != del.expected)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  struct DataStruct
  {
    double key1;
    double key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& in, DataStruct& data)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    StreamGuard s_guard(in);
    using del = Delimiter;
    int number = 0;
    in >> del{'('};
    int max_keys = 3;
    for (int i = 0; i < max_keys; i++)
    {
      in >> del{':'} >> del{'k'} >> del{'e'} >> del{'y'};
      in >> number;
      if (number == 1)
      {
        in >> data.key1;
      }
      else if (number == 2)
      {
        in >> data.key2;
      }
      else if (number == 3)
      {
        in >> del{'"'};
        std::getline(in, data.key3, '"');
      }
    }
    in >> del{':'} >> del{')'};
    return in;
  }
  std::ostream& operator<<(std::ostream& out, const DataStruct& data)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    StreamGuard s_guard(out);
    out << "(:key1 " << data.key1 << ":key2 " << data.key2 << ":key3 " << '"' << data.key3 << "\":)";
    return out;
  }
  bool operator<(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    if (lhs.key2 != rhs.key2)
    {
      return lhs.key2 < rhs.key2;
    }
    return lhs.key3.size() < rhs.key3.size();
  }
}



int main()
{
  using namespace altun;
  DataStruct a{0, 0, ""};
  std::cin >> a;
  std::cout << a << '\n';
}
