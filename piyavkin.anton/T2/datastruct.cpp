#include "datastruct.hpp"

std::istream& piyavkin::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  unsigned long long hex;
  long long num;
  unsigned long long den;
  std::string str;
  in >> std::hex >> hex;
  in >> std::dec >> num >> den >> str;
  if (in)
  {
    data.key1 = hex;
    data.key2.first = num;
    data.key2.second = den;
    data.key3 = str;
  }
  return in;
}

std::ostream& piyavkin::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << std::hex << data.key1;
  out << std::dec << ' ' << data.key2.first << ' ' << data.key2.second << ' ' << data.key3;
  return out;
}