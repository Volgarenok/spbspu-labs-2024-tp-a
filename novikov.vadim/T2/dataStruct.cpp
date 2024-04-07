#include "dataStruct.hpp"
#include "delimiterI.hpp"
#include "valueI.hpp"

bool novikov::operator<(const DataStruct& value1, const DataStruct& value2)
{
  if (value1.key1 == value2.key1)
  {
    if (value1.key2 == value2.key2)
    {
      return value1.key3.size() < value2.key3.size();
    }
    return value1.key2 < value2.key2;
  }
  return value1.key1 < value2.key1;
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
  using chr_del = StrictCaseCharDelimiterI;
  using str_del = StrictCaseStringDelimiterI;
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
  out << "(:key1 0" << std::oct << value.key1;
  out << ":key2 0x" << std::hex << std::uppercase << value.key2;
  out << ":key3 \"" << value.key3  << "\":)";
  return out;
}
