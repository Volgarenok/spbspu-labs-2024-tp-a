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
