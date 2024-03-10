#include "DataStruct.hpp"
#include <iostream>

std::istream& sazanov::operator>>(std::istream& in, sazanov::DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  unsigned long long key1 = 0;
  char key2 = 0;
  std::string key3;
  std::cin >> key1 >> key2 >> key3;
  if (in)
  {
    value = sazanov::DataStruct(key1, key2, key3);
  }

  return in;
}
