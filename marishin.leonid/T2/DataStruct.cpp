#include "DataStruct.hpp"
#include "value.hpp"

std::istream& marishin::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimeterchar;
  using dell = Delimeterstring;
  in >> del{ '(' };
  size_t keys = 3;
  size_t y = 0;
  for (size_t i = 0; i < keys; ++i)
  {
    in >> dell{ ":key" } >> y;
    if (y == 1)
    {
      in >> DblSci{ data.key1 };
    }
    else if (y == 2)
    {
      in >> RatLsp{ data.key2 };
    }
    else if (y == 3)
    {
      in >> StringStr{ data.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> dell{ ":)" };
  return in;
}

std::ostream& marishin::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << DoubleSci{ value.key1 };
  out << ":key2 (:N " << value.key2.first << ":D " << value.key2.second << ":)";
  out << ":key3 " << '"' << value.key3 << '"' << ":)";
  return out;
}

bool marishin::DataStruct::operator<(const DataStruct& data) const
{
  if (key1 == data.key1)
  {
    if (key2.first * data.key2.second == key2.second * data.key2.first)
    {
      return key3.size() < data.key3.size();
    }
    return key2.first * data.key2.second < key2.second * data.key2.first;
  }
  return key1 < data.key1;
}

bool marishin::DataStruct::operator>=(const DataStruct& data) const
{
  return !(*this < data);
}

bool marishin::DataStruct::operator<=(const DataStruct& data) const
{
  return !(data < *this);
}

bool marishin::DataStruct::operator>(const DataStruct& data) const
{
  return (data < *this);
}

bool marishin::DataStruct::operator==(const DataStruct& data) const
{
  return !(*this < data) && !(data < *this);
}

bool marishin::DataStruct::operator!=(const DataStruct& data) const
{
  return !(data == *this);
}
