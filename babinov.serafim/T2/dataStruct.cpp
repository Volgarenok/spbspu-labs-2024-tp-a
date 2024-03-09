#include "dataStruct.hpp"
#include <bitset>

bool babinov::DataStruct::operator>(const DataStruct& right) const
{
  if (key1 != right.key1)
  {
    return key1 > right.key1;
  }
  if (key2 != right.key2)
  {
    return key2 > right.key2;
  }
  return key3 > right.key3;
}

bool babinov::DataStruct::operator<(const DataStruct& right) const
{
  return (right > *this);
}

bool babinov::DataStruct::operator>=(const DataStruct& right) const
{
  return !(*this < right);
}

bool babinov::DataStruct::operator<=(const DataStruct& right) const
{
  return !(right < *this);
}

bool babinov::DataStruct::operator==(const DataStruct& right) const
{
  return ((right <= *this) && (*this <= right));
}

bool babinov::DataStruct::operator!=(const DataStruct& right) const
{
  return !(*this == right);
}

std::string toBin(unsigned long long dec)
{
  std::bitset< 64 > bin(dec);
  std::string strBin = bin.to_string();
  strBin.erase(0, strBin.find_first_not_of('0'));
  return strBin;
}

std::istream& babinov::operator>>(std::istream& in, DataStruct& data) {};
std::ostream& babinov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << "(:key1 " << data.key1 << "ull";
    out << ":key2 " << "0b" << toBin(data.key2);
    out << ":key3 " << '"' << data.key3 << '"' << ":)";
  }
  return out;
}
