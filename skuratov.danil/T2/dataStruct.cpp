#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "nameOfKeys.hpp"

bool skuratov::DataStruct::operator<(const DataStruct& diff) const
{
  return (key1 == diff.key1) ? ((key2 == diff.key2) ? (key3.length() < diff.key3.length()) : (key2 < diff.key2)) : (key1 < diff.key1);
}

std::istream& skuratov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  int num = 0;
  std::string numOfKey = "";
  in >> del{ '(' };
  while (in && (num < 3))
  {
    in >> del{ ':' } >> numOfKey;
    if ((numOfKey == "key1") && (num != 3))
    {
      in >> UllKey{ value.key1 };
      ++num;
    }
    else if ((numOfKey == "key2") && (num != 3))
    {
      in >> CharKey{ value.key2 };
      ++num;
    }
    else if ((numOfKey == "key3") && (num != 3))
    {
      in >> StringKey{ value.key3 };
      ++num;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> del{ ':' };
  in >> del{ ')' };
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
