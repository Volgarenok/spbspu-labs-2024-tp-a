#include "dataStruct.hpp"
#include "charDelimiterI.hpp"
#include "stringDelimiterI.hpp"
#include "valueI.hpp"
#include "valueO.hpp"

bool novikov::operator<(const DataStruct& other) const
{
  if (key1 == other.key1)
  {
    if (key2 == other.key2)
    {
      return (key3.size() < other.key3.size());
    }
    return (key2 < other.key2);
  }
  return (key1 < other.key1);
}

bool novikov::operator>(const DataStruct& other) const
{
  return (other < *this);
}

bool novikov::operator<=(const DataStruct& other) const
{
  return !(other < *this);
}

bool novikov::operator>=(const DataStruct& other) const
{
  return !(*this < other);
}

bool novikov::operator==(const DataStruct& other) const
{
  if (key1 == other.key1)
  {
    if (key2 == other.key2)
    {
      return key3.size() == other.key3.size();
    }
  }
}

bool novikov::operator!=(const DataStruct& other) const
{
  return !(*this == other);
}

std::istream& novikov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    using chr_del = CharDelimiterI;
    using str_del = StringDelimiterI;
    using oct_val = OctValueI;
    using hex_val = HexValueI;
    using str_val = StrValueI;
    constexpr std::size_t FIELDS_COUNT = 3;
    DataStruct read_struct = {0, 0, ""};
    in >> chr_del{'('};
    for (std::size_t i = 0; (i < FIELDS_COUNT) && in; ++i)
    {
      char field = '\0';
      in >> str_del{":key"} >> field;
      switch (field)
      {
      case '1':
        in >> oct_val{read_struct.key1};
        break;
      case '2':
        in >> hex_val{read_struct.key2};
        break;
      case '3':
        in >> str_val{read_struct.key3};
        break;
      default:
        in.setstate(std::ios::failbit);
        break;
      }
    }
    in >> str_del{":)"};
    if (in)
    {
      value = read_struct;
    }
  }
  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    using oct_val = OctValueO;
    using hex_val = HexValueO;
    using str_val = StrValueO;
    out << '(';
    out << ":key1 " << oct_val{value.key1};
    out << ":key2 " << hex_val{value.key2};
    out << ":key3 " << str_val{value.key3};
    out << ":)";
  }
  return out;
}
