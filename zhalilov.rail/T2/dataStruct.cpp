#include "dataStruct.hpp"

#include <iomanip>
#include <iostream>

#include "inputDataDetail.hpp"
#include "ioFormatGuard.hpp"

bool zhalilov::DataStruct::operator<(const DataStruct &other) const
{
  if (key1 < other.key1)
  {
    return true;
  }
  if (key2 < other.key2)
  {
    return true;
  }
  if (key3 < other.key3)
  {
    return true;
  }
  return false;
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
  ioFormatGuard fmtguard(out);
  out << std::fixed << std::setprecision(1) << std::scientific;
  out << "(:key1 " << data.key1;
  out << ":key2 " << data.key2 << "ll";
  out << ":key3 ";
  out << std::quoted(data.key3);
  out << ":)";
  return out;
}
