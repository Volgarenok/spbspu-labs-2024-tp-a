#include "dataStruct.hpp"

bool belokurskaya::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 < other.key1)
  {
    return true;
  }
  else if (key1 == other.key1)
  {
    if (key2 < other.key2)
    {
      return true;
    }
    else if (key2 == other.key2)
    {
      return key3 < other.key3;
    }
    return false;
  }
  return false;
}
