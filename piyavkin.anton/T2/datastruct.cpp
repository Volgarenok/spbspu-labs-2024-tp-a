#include "datastruct.hpp"
#include "delimeter.hpp"
#include "inputkey.hpp"

std::istream& piyavkin::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (guard)
  {
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
  }
  return in;
}

std::ostream& piyavkin::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    out << "(:key1 " << std::hex << data.key1 << std::dec << "ull";
    out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
    out << ":key3 " << '"' << data.key3 << '"' << ":)";
  }
  return out;
}

bool piyavkin::DataStruct::operator<(DataStruct& data)
{
  if (key1 == data.key1)
  {
    if (key2.first * data.key2.second == key2.second * data.key2.first)
    {
      return key3 < data.key3;
    }
    return key2.first * data.key2.second < key2.second * data.key2.first;
  }
  return key1 < data.key1;
}

bool piyavkin::DataStruct::operator>=(DataStruct& data)
{
  return !(*this < data);
}

bool piyavkin::DataStruct::operator<=(DataStruct& data)
{
  return !(data < *this);
}

bool piyavkin::DataStruct::operator>(DataStruct& data)
{
  return (data < *this);
}

bool piyavkin::DataStruct::operator==(DataStruct& data)
{
  return ((key1 == data.key1) && (key2.first == data.key2.first)
    && (key2.second == data.key2.second) && (key3 == data.key3));
}

bool piyavkin::DataStruct::operator!=(DataStruct& data)
{
  return !(data == *this);
}
