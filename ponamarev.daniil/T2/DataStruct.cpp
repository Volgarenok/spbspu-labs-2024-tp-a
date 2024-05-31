#include "DataStruct.h"
#include "Delimeter.h"
#include "ioFormatGuard.h"
#include <iostream>
#include <iomanip>
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
  using ull = UnsignedLongLongHexIO;
  using str = StringIO;
  using rat = RationalIO;
  in >> sep{ '(' };
  for (int i = 0; i < 3; i++)
  {
    char key = 0;
    in >> sep{ ':' } >> sep{ 'k' } >> sep{ 'e' } >> sep{ 'y' } >> key;
    if (!in)
    {
      break;
    }
    if (key == '1')
    {
      in >> ull{ input.key1 };
    }
    else if (key == '2')
    {
      in >> rat{ input.key2 };
    }
    else if (key == '3')
    {
      in >> str{ input.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> sep{ ':' } >> sep{ ')' };
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
  out << std::hex << std::uppercase << obj.key1 << std::dec;
  out << ":key2 ";
  out << "(:N " << obj.key2.first << ":D " <<obj.key2.second << ":)";
  out << ":key3 ";
  out << "\"";
  out << obj.key3;
  out << "\"";
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
