#include "DataStruct.hpp"
#include <iomanip>
#include <Delimeter.hpp>

std::istream & erfurt::operator>>(std::istream & in, DataStruct & value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  long long key1 = 0;
  unsigned long long key2 = 0;
  std::string key3 = "";
  std::size_t keyIndex = 0;

  in >> Delimeter{"("};
  for (std::size_t i = 0; i < 3 && in; ++i)
  {
    in >> Delimeter{":key"} >> keyIndex;
    switch (keyIndex)
    {
    case 1:
      in >> key1 >> Delimeter{"ll"};
      break;
    case 2:
      in >> key2 >> Delimeter{"ull"};
      break;
    case 3:
      in >> Delimeter{"\""};
      std::getline(in, key3,'"');
      break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
  }
  in >> Delimeter{ ":)" };
  if (in)
  {
    value = DataStruct{key1, key2, key3};
  }
  return in;
}

std::ostream & erfurt::operator<<(std::ostream & out, const DataStruct & value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << value.key1 << "ll"
      << ":key2 " << value.key2 << "ull"
      << ":key3 " << std::quoted(value.key3) << ":)";
  return out;
}

bool erfurt::DataStruct::operator<(const DataStruct & value) const
{
  if (key1 == value.key1)
  {
    if (key2 == value.key2)
    {
      return key3.length() < value.key3.length();
    }
    return key2 < value.key2;
  }
  return key1 < value.key1;
}
