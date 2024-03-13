#include "dataStruct.hpp"
#include "delimiterI.hpp"
#include "valueI.hpp"

bool novikov::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 == other.key1)
  {
    if (key2 == other.key2)
    {
      return key3.size() < other.key3.size();
    }
    return key2 < other.key2;
  }
  return key1 < other.key1;
}

bool novikov::DataStruct::operator>(const DataStruct& other) const
{
  return other < *this;
}

bool novikov::DataStruct::operator<=(const DataStruct& other) const
{
  return !(other < *this);
}

bool novikov::DataStruct::operator>=(const DataStruct& other) const
{
  return !(*this < other);
}

bool novikov::DataStruct::operator==(const DataStruct& other) const
{
  return !(*this < other) && !(other < *this);
}

bool novikov::DataStruct::operator!=(const DataStruct& other) const
{
  return !(*this == other);
}

std::istream& novikov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  constexpr std::size_t FIELDS_COUNT = 3;
  DataStruct read_struct{ 0, 0, "" };
  using chr_del = CharDelimiterI;
  using str_del = StringDelimiterI;
  in >> chr_del{ '(' };
  for (std::size_t i = 0; (i < FIELDS_COUNT) && in; ++i)
  {
    char field{};
    in >> str_del{ ":key" } >> field;
    switch (field)
    {
    case '1':
      using oct_val = OctValueI;
      in >> oct_val{ read_struct.key1 };
      break;
    case '2':
      using hex_val = HexValueI;
      in >> hex_val{ read_struct.key2 };
      break;
    case '3':
      using str_val = StrValueI;
      in >> str_val{ read_struct.key3 };
      break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
  }
  in >> str_del{ ":)" };
  if (in)
  {
    value = read_struct;
  }
  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(';
  out << ":key1 " << std::oct << value.key1;
  out << ":key2 " << std::hex << value.key2;
  out << ":key3 \"" << value.key3 << '"';
  out << ":)";
  return out;
}
