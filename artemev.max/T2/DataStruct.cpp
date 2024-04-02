#include "DataStruct.hpp"
#include <bitset>
#include <algorithm>
#include "Delimiter.hpp"
#include "ScopeGuard.hpp"

std::string getBinNumber(unsigned long long value)
{
  std::string bin;

  do
  {
    bin.push_back('0' + (value & 1));
  }
  while (value >>= 1);

  std::reverse(bin.begin(), bin.end());
  return bin;
}

bool artemev::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }

  else if (key2 != other.key2)
  {
    return key2 < other.key2;
  }

  return (key3.length() <= other.key3.length());
}
