#include "DataStruct.hpp"

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

std::ostream& kuzmina::operator<<(std::ostream&, const DataStruct&) {}
