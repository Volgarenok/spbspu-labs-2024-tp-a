#include "dataStruct.hpp"

#include <iostream>

#include "dataIO.hpp"
#include "FormatGuard.hpp"

namespace serter
{
  std::istream& operator>>(std::istream& in, DataStruct& value)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
    for (size_t i = 1; i <= 3; i++)
    {
      size_t num = 0;
      in >> LabelIO{ "key" } >> num;
      if (num == 1)
      {
        in >> DoubleIO{ input.key1 };
      }
      else if (num == 2)
      {
        in >> UnsignedllIO{ input.key2 };
      }
      else if (num == 3)
      {
        in >> StringIO{ input.key3 };
      }
      if (!sentry)
      {
        return in;
      }
    }
    in >> DelimiterIO{ ')' };
    if (in)
    {
      value = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& value)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    FormatGuard guard(out);
    out << "(";
    out << ":key1 " << fromDoubleToScientific(value.key1);
    out << ":key2 0b" << (value.key2 == 0 ? "" : "0") << fromULLtoBinary(value.key2);
    out << ":key3 \"" << value.key3;
    out << "\":)";
    return out;
  }

  bool operator<(const DataStruct& left, const DataStruct& right)
  {
    if (left.key1 != right.key1)
    {
      return left.key1 < right.key1;
    }
    else if (left.key2 != right.key2)
    {
      return left.key2 < right.key2;
    }
    else
    {
      return left.key3.length() < right.key3.length();
    }
  }
}

