#include "dataStruct.hpp"

std::istream& skuratov::operator>>(std::istream& in, DataStruct& value)
{
  return in;
}
std::ostream& skuratov::operator<<(std::ostream& out, const DataStruct& value)
{
  return out;
}
