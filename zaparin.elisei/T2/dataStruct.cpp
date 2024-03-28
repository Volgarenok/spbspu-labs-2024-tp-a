#include "dataStruct.hpp"
#include "delimeter.hpp"
#include <string>

std::istream& zaparin::operator>>(std::istream& in, zaparin::DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = Delimeter;

  in >> del{ "(" };
  size_t keysCount = 0;
  DataStruct temp{ 0, {0, 0}, "" };

  while (in && keysCount < 3)
  {
    size_t keyType = 0;
    in >> del{ ":key" } >> keyType;

    switch (keyType)
    {
    case 1:
      in >> del{ "0b" } >> temp.key1;
      keysCount++;
      break;

    case 2:
      in >> del{ "(:N" } >> temp.key2.first >> del{ ":D" } >> temp.key2.second >> del{ ":)" };
      keysCount++;
      break;

    case 3:
      in >> del{ "\"" };
      std::getline(in, temp.key3, '\"');
      keysCount++;
      break;

    default:
      in.setstate(std::ios::failbit);
      break;
    }
  }

  in >> del{ ":)" };
  if (in)
  {
    data = temp;
  }

  return in;
}

std::ostream& zaparin::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  out << "(:key1 0b" << (data.key1 == 0 ? "" : "0") << data.key1;
  out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
  out << ":key3 \"" << data.key3 << "\":)";

  return out;
}

bool zaparin::DataStruct::operator<(const DataStruct& data)
{
  if (key1 == data.key1)
  {
    if (key2 == data.key2)
    {
      return (key3 < data.key3);
    }
    return (key2 < data.key2);
  }
  return (key1 < data.key1);
}

