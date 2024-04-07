#include "Delimeter.h"
#include "DataStruct.h"
#include "ioFormatGuard.h"
#include "Delimeter.h"
#include "DataStruct.h"
#include <string>
#include <iostream>

std::istream& ponamarev::operator>>(std::istream& in, DataStruct&& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
  return in;
  }
  const size_t COUNT_KEYS = 3;
  DataStruct tmp{ 0x0, {0, 0} , "" };
  using sep = DelimeterIO;
  in >> sep{ '(' };
  for (size_t i = 0; i < COUNT_KEYS; ++i)
  {
    char order = 0;
    in >> sep{ ':' } >> sep{ 'k' } >> sep{ 'e' } >> sep{ 'y' } >> order;
    if (!in)
    {
      break;
    }

    if (order == '1')
    {
      in >> UnsignedLongLongHexIO{ tmp.key1 };
    }
    else if (order == '2')
    {
      in >> RationalIO{ tmp.key2 };
    }
    else if (order == '3')
    {
      in >> StringIO{ tmp.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }

  in >> sep{ ':' } >> sep{ ')' };
  if (in)
  {
    data = tmp;
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
