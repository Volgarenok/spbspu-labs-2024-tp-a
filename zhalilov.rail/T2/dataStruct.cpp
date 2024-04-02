#include "dataStruct.hpp"

#include <iomanip>
#include <iostream>

#include "inputDataDetail.hpp"
#include "ioFormatGuard.hpp"

namespace zhalilov
{
  std::ostream &outputScientific(std::ostream &out, double num)
  {
    ioFormatGuard fmtguard(out);
    out << std::fixed << std::setprecision(1);
    int exp = 0;
    while (num > 1.0)
    {
      num /= 10;
      exp++;
    }
    while (num < 1.0)
    {
      num *= 10;
      exp--;
    }
    out << num << 'e' << exp;
    return out;
  }
}

bool zhalilov::DataStruct::operator<(const DataStruct &other) const
{
  if (key1 == other.key1)
  {
    if (key2 == other.key2)
    {
      return key3 < other.key3;
    }
    return key2 < other.key2;
  }
  return key1 < other.key1;
}

bool zhalilov::DataStruct::operator>(const DataStruct &other) const
{
  return other < *this;
}

bool zhalilov::DataStruct::operator==(const DataStruct &other) const
{
  return key1 == other.key1 && key2 == other.key2 && key3 == other.key3;
}

bool zhalilov::DataStruct::operator<=(const DataStruct &other) const
{
  return !(other > *this);
}

bool zhalilov::DataStruct::operator>=(const DataStruct &other) const
{
  return !(*this < other);
}

std::istream &zhalilov::operator>>(std::istream &in, DataStruct &data)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  DataStruct input;
  in >> detail::DelimiterI{ '(' } >> detail::DelimiterI{ ':' };
  detail::inputKey(in, input) >> detail::DelimiterI{ ':' };
  detail::inputKey(in, input) >> detail::DelimiterI{ ':' };
  detail::inputKey(in, input);
  in >> detail::DelimiterI{ ':' } >> detail::DelimiterI{ ')' };
  if (in)
  {
    data = input;
  }
  return in;
}

std::ostream &zhalilov::operator<<(std::ostream &out, const DataStruct &data)
{
  out << "(:key1 ";
  outputScientific(out, data.key1);
  out << ":key2 " << data.key2 << "ll";
  out << ":key3 ";
  out << std::quoted(data.key3);
  out << ":)";
  return out;
}
