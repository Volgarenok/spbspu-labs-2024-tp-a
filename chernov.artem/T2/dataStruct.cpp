#include "dataStruct.hpp"
#include "streamGuard.hpp"
#include "delimiters.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstddef>

namespace chernov
{
  std::istream& operator>>(std::istream& input, DataStruct& obj)
  {
    std::istream::sentry sentry(input);
    if (!sentry)
    {
      return input;
    }
    input >> DelimiterIO{'('};
    for (int i = 0; i < 3; i++)
    {
      size_t num = 0;
      input >> StringIO{":key"};
      input >> num;

      if (num == 1)
      {
        input >> DoubleIO{obj.key1};
      }

      if (num == 2)
      {
        input >> UnsignedLongLongIO{obj.key2};
      }

      if (num == 3)
      {
        input >> StringIO{obj.key3};
      }
      else
      {
        input.setstate(std::ios::failbit);
      }
    }
    input >> StringIO{":)"};
    return input;
  }

  std::ostream& operator<<(std::ostream& output, const DataStruct& obj)
  {
    std::ostream::sentry sentry(output);
    if (!sentry)
    {
      return output;
    }
    chernov::StreamGuard guard(output);
  }

  bool operator<(const DataStruct& value1, const DataStruct& value2)
  {
    return (value1.key1 < value2.key1) || (value1.key2 < value2.key2) || (value1.key3.size() < value2.key3.size());
  }
}
