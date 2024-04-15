#include "dataStruct.hpp"
#include "delimiter.hpp"

bool skuratov::DataStruct::operator<(const DataStruct& diff) const
{
  return (key1 != diff.key1) ? (key1 < diff.key1) : ((key2 != diff.key2) ? (key2 < diff.key2) : (key3 < diff.key3));
}

std::istream& skuratov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  using lDel = LineDelimiter;
  in >> del{ '(' };
  for (size_t i = 0; i < 3; ++i)
  {
    int numOfKey = 0;
    in >> lDel{ ":key" } >> numOfKey;
    if (numOfKey == 1)
    {
      in >> del{ '0' } >> del{ 'x' } >> std::hex >> value.key1;
    }
    if (numOfKey == 2)
    {
      in >> del{ '\'' } >> value.key2 >> del{ '\'' };
    }
    if (numOfKey == 3)
    {
      in >> del{ '"' };
      std::getline(in, value.key3, '"');
    }
  }
  in >> lDel{ ":)" };
  return in;
}

std::ostream& skuratov::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 0x" << std::hex << std::uppercase << value.key1;
  out << ":key2 '" << value.key2;
  out << "':key3 \"" << value.key3 << '"';
  out << ":)";
  return out;
}
