#include "datastruct.hpp"
#include "delimeter.hpp"
#include "inputkey.hpp"

std::istream& piyavkin::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using dc = DelimeterChar;
  using ds = DelimeterString;
  unsigned long long hex = 0;
  long long num = 0;
  unsigned long long den = 0;
  std::string str = "";
  size_t numberKey = 0;
  const size_t countKey = 3;
  in >> dc{'('};
  for (size_t i = 0; i < countKey; ++i)
  {
    in >> ds{":key"} >> numberKey;
    inputKey(in, numberKey, data);
  }
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