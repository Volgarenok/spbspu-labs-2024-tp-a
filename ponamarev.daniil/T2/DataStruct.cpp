#include "DataStruct.h"
#include "Delimeter.h"
#include "ioFormatGuard.h"
#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>
#include <iostream>

std::istream& ponamarev::operator>>(std::istream& in, DataStruct& obj)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimeterIO;
    using label = LabelIO;
    using ull = UnsignedLongLongHexIO;
    using str = StringIO;
    using rat = RationalIO;
    in >> sep{ '(' };
    in >> sep{ ':' };
    in >> label{ "key1" } >> sep{ ' ' } >> ull{ input.key1 };
    in >> sep{ ':' };
    in >> label{ "key2" } >> sep{ ' ' } >> rat{ input.key2 };
    in >> sep{ ':' };
    in >> label{ "key3" } >> sep{ ' ' } >> str{ input.key3 };
    in >> sep{ ':' };
    in >> sep{ ')' };
  }
  if (in)
  {
    obj = input;
  }
  return in;
}

std::ostream& ponamarev::operator<<(std::ostream & out, const DataStruct & obj)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  ioFormatGuard FormatGuard(out);
  out << "(:key1 0x";
  out << obj.key1;
  out << ":key2 ";
  out << "(:N " << obj.key2.first << ":D " <<obj.key2.second << ":)";
  out << ":key3 ";
  out << obj.key3;
  out << ":)";
  return out;
}

bool ponamarev::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 == other.key1)
  {
    if (key2 == other.key2)
    {
      return key3.size() < other.key3.size();
    }
    return key2 < other.key2;
  }
  return key1 < other.key1;
}
