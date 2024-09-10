#include "DataStruct.hpp"
#include <cmath>
#include <iomanip>
#include <Delimeter.hpp>
#include "Key.hpp"

bool kuznetsov::DataStruct::operator<(const DataStruct& data) const
{
  if (key1 != data.key1)
  {
    return key1 < data.key1;
  }
  else if (std::abs(key2) != std::abs(data.key2))
  {
    return std::abs(key2) < std::abs(data.key2);
  }
  return key3.length() < data.key3.length();
}

std::ostream& kuznetsov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << data.key1 << "ull";
  out << ":key2 #c(" << std::setprecision(1) << std::fixed << data.key2.real() << " " << data.key2.imag() << ")";
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
}

std::istream& kuznetsov::operator>>(std::istream& in, DataStruct& data)
{
  using delchr = DelimeterChar;
  using delstr = DelimeterString;
  size_t keyNumber = 0;
  in >> delstr{ "(:" };
  for (int i = 0; i < 3; ++i)
  {
    in >> delstr{ "key" } >> keyNumber;
    if (keyNumber == 1)
    {
      in >> UllKey{ data.key1 };
    }
    else if (keyNumber == 2)
    {
      in >> ComplexKey{ data.key2 };
    }
    else if (keyNumber == 3)
    {
      in >> StringKey{ data.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> delchr{ ':' };
  }
  in >> delchr{ ')' };
  return in;
}

