#include "datastruct.hpp"
#include <delimeter.hpp>

void inputKey(std::istream& in, size_t numberKey, piyavkin::DataStruct& data)
{
  using namespace piyavkin;
  using ds = DelimeterString;
  if (numberKey == 1)
  {
    unsigned long long hex = 0;
    in >> std::hex >> hex >> std::dec >> ds{"ull"};
    if (in)
    {
      data.key1 = hex;
    }
  }
  else if (numberKey == 2)
  {
    long long int num = 0;
    unsigned long long den = 0;
    in >> ds{"(:n"} >> num >> ds{":d"} >> den >> ds{":)"};
    if (in)
    {
      data.key2.first = num;
      data.key2.second = den;
    }
  }
  else if (numberKey == 3)
  {
    std::string str = "";
    in >> str;
    if (in)
    {
      data.key3 = str;
    }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
}

std::istream& piyavkin::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using dc = DelimeterChar;
  using ds = DelimeterString;
  size_t numberKey = 0;
  const size_t countKey = 3;
  in >> dc{'('};
  for (size_t i = 0; i < countKey && in; ++i)
  {
    in >> ds{":key"} >> numberKey;
    inputKey(in, numberKey, data);
  }
  in >> ds{":)"};
  return in;
}

std::istream& piyavkin::operator>>(std::istream& in, std::string& str)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> DelimeterChar{'"'};
  char symbol = 0;
  size_t i = 0;
  in >> std::noskipws;
  while (symbol != '"' && str[i] != '\\')
  {
    in >> symbol;
    if (symbol != '"' && str[i] != '\\')
    {
      str += symbol;
      ++i;
    }
  }
  in >> std::skipws;
  return in;
}

std::ostream& piyavkin::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << std::hex << data.key1 << std::dec << "ull";
  out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
  out << ":key3 " << '"' << data.key3 << '"' << ":)";
  return out;
}

bool piyavkin::DataStruct::operator<(const DataStruct& data) const
{
  if (key1 == data.key1)
  {
    if (key2.first * data.key2.second == key2.second * data.key2.first)
    {
      return key3.size() < data.key3.size();
    }
    return key2.first * data.key2.second < key2.second * data.key2.first;
  }
  return key1 < data.key1;
}

bool piyavkin::DataStruct::operator>=(const DataStruct& data) const
{
  return !(*this < data);
}

bool piyavkin::DataStruct::operator<=(const DataStruct& data) const
{
  return !(data < *this);
}

bool piyavkin::DataStruct::operator>(const DataStruct& data) const
{
  return (data < *this);
}

bool piyavkin::DataStruct::operator==(const DataStruct& data) const
{
  return !(*this < data) && !(data < *this);
}

bool piyavkin::DataStruct::operator!=(const DataStruct& data) const
{
  return !(data == *this);
}
