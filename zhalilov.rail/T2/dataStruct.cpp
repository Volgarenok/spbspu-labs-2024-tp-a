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

zhalilov::DataStruct::DataStruct(double key1, long long key2, const std::string &key3):
  key1_(key1),
  key2_(key2),
  key3_(key3)
{}

std::istream &zhalilov::operator>>(std::istream &in, zhalilov::DataStruct &data)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }

  return in;
}


