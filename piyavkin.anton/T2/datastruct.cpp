#include "datastruct.hpp"
#include "delimeter.hpp"

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
  in >> Delimeter{'('};
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
  if (guard)
  {
    out << "(:key1 " << std::hex << data.key1 << "ull";
    out << ":key2 (:N " << std::dec << data.key2.first << ":D " << data.key2.second << ":)";
    out << ":key3 " << '"' << data.key3 << '"' << ":)";
  }
  return out;
}