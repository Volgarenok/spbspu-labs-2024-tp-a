#include "DataStruct.hpp"
#include <iostream>
#include "DelimiterI.hpp"

bool kuzmina::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 == other.key1)
  {
    if (key2.first / key2.second == other.key2.first / other.key2.second)
    {
      return key3.length() < other.key3.length();
    }
    return key2.first / key2.second < other.key2.first / other.key2.second;
  }
  return key1 < other.key1;
}

std::istream& kuzmina::operator>>(std::istream&, DataStruct&) {}

std::ostream& kuzmina::operator<<(std::ostream&, const DataStruct&)
std::ostream& kuzmina::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  out << "(:key1 " << value.key1 << "ll"
      << ":key2 (:N " << value.key2.first << ":D " << value.key2.second<< ":)"
      << ":key3 \"" << value.key3 << "\":)";

  return out;
}
