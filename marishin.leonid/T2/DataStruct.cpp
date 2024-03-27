#include "DataStruct.hpp"
#include "delimeter.hpp"
#include "inputFunctions.hpp"

std::istream& marishin::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    using del = Delimeterchar;
    using dell = Delimeterstring;
    in >> del{ '(' };
    size_t keys = 3;
    size_t y = 0;
    for (size_t i = 0; i < keys; ++i)
    {
      in >> dell{ ":key" } >> y;
      inputKeys(in, y, data);
    }
    in >> dell{ ":)" };
  }
  return in;
}

std::istream& marishin::operator>>(std::istream& in, std::string& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    in >> Delimeterchar{ '"' };
    std::getline(in, exp, '"');
  }
  return in;
}

std::ostream& marishin::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    std::string formatted;
    printScientific(formatted, value.key1);
    out << "(:key1 " << formatted;
    out << ":key2 (:N " << value.key2.first << ":D " << value.key2.second << ":)";
    out << ":key3 " << '"' << value.key3 << '"' << ":)";
  }
  return out;
}

bool marishin::DataStruct::operator<(const DataStruct& data) const
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
