#include "inputData.hpp"

#include <istream>
#include <cctype>

namespace zhalilov
{
  struct DelimiterI
  {
    char expected;
  };

  struct DoubleI
  {
    double &num;
  };

  struct LongLongI
  {
    long long &num;
  };

  std::istream &operator>>(std::istream &in, DelimiterI &&symb)
  {
    std::istream::sentry s(in);
    if (!s)
    {
      return in;
    }
    char temp = 0;
    in >> temp;
    if (temp != std::tolower(symb.expected))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}

std::istream &zhalilov::operator>>(std::istream &in, zhalilov::DataStruct &data)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }

  return in;
}
