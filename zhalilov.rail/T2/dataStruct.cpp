#include "dataStruct.hpp"

#include <istream>

namespace zhalilov
{
  struct SymbolI
  {
    char expected;
  };
  std::istream &operator>>(std::istream &in, SymbolI &&symb)
  {
    std::istream::sentry s(in);
    if (!s)
    {
      return in;
    }
    char temp = 0;
    in >> temp;
    if (temp != symb.expected)
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


