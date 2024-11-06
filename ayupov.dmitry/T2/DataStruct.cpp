#include "DataStruct.hpp"

#include <istream>
#include <ostream>
#include <string>
#include <iomanip>
#include <Delimiter.hpp>

#include "KeyI.hpp"

std::istream& ayupov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> DelimiterChar{'('};
  int keyNum = 0;
  for (int i = 0; i < 3; i++)
  {
    in >> DelimiterString{":key"} >> keyNum;
    if (keyNum == 1)
    {
      in >> DblSciI{value.key1};
    }
    else if (keyNum == 2)
    {
      in >> CharI{value.key2};
    }
    else if (keyNum == 3)
    {
      in >> StringI{value.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> DelimiterString{":)"};
  return in;
}
std::ostream& ayupov::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:key1 ";
  double dbl = value.key1;
  out << std::fixed << std::setprecision(1) << DblSciI{ dbl };
  out << ":key2 '" << value.key2 << '\'';
  out << ":key3 \"" << value.key3 << "\":)";
  return out;
}
bool ayupov::DataStruct::operator<(const DataStruct &other) const
{
  if (key1 == other.key1)
  {
    if (key2 == other.key2)
    {
      return key3.size() < key3.size();
    }
    return key2 < other.key2;
  }
  return key1 < other.key1;
}
