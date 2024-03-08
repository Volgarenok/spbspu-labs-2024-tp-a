#include "inputkey.hpp"

void piyavkin::inputKey(std::istream& in, size_t numberKey, DataStruct& data)
{
  if (numberKey == 1)
  {
    unsigned long long hex = 0;
    in >> std::hex >> hex >> std::dec;
    data.key1 = hex;
  }
}