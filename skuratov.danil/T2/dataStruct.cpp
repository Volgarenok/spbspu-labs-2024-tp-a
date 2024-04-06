#include "dataStruct.hpp"
#include "delimiter.hpp"

bool skuratov::DataStruct::operator<(const DataStruct& different) const
{}

std::istream& skuratov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterI;
  unsigned long long key1 = 0;
  char key2 = 0;
  std::string key3 = "";
  in >> del{ '(' } >> del{ ':' } >> del{ ')' };

  if (in)
  {
    value = DataStruct();
  }
  return in;
}
std::ostream& skuratov::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << value.key1 << ":key2 " << value.key2 << ":key3 " << value.key3 << ":)" << "\n";
  return out;
}
