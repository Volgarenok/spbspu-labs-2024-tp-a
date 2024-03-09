#include "dataStruct.hpp"

bool babinov::DataStruct::operator>(const DataStruct& right) const
{
  if (key1 != right.key1)
  {
    return key1 > right.key1;
  }
  if (key2 != right.key2)
  {
    return key2 > right.key2;
  }
  return key3 > right.key3;
}

bool babinov::DataStruct::operator<(const DataStruct& right) const
{
  return (right > *this);
}

bool babinov::DataStruct::operator>=(const DataStruct& right) const
{
  return !(*this < right);
}

bool babinov::DataStruct::operator<=(const DataStruct& right) const
{
  return !(right < *this);
}

bool babinov::DataStruct::operator==(const DataStruct& right) const
{
  return ((right <= *this) && (*this <= right));
}

bool babinov::DataStruct::operator!=(const DataStruct& right) const
{
  return !(*this == right);
}

std::istream& babinov::operator>>(std::istream& in, DataStruct& data) {};
std::ostream& babinov::operator<<(std::ostream& in, const DataStruct& data) {};
