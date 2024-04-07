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
