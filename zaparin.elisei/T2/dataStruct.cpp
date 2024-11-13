#include "dataStruct.hpp"
#include <string>
#include "delimeter.hpp"
#include "keyTypes.hpp"

std::istream& zaparin::operator>>(std::istream& in, zaparin::DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimeter{ "(" };
  size_t keysCount = 0;
  DataStruct temp{ 0, {0, 0}, "" };

  while (in && keysCount < 3)
  {
    size_t keyType = 0;
    in >> KeyType{ keyType };

    switch (keyType)
    {
    case 1:
      in >> UllBin{ temp.key1 };
      keysCount++;
      break;

    case 2:
      in >> RatLsp{ temp.key2 };
      keysCount++;
      break;

    case 3:
      in >> String{ temp.key3 };
      keysCount++;
      break;

    default:
      in.setstate(std::ios::failbit);
      break;
    }
  }

  in >> Delimeter{ ":)" };
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
      return (key3.size() < data.key3.size());
    }
    if (key2.first == data.key2.first)
    {
      return (key2.second < data.key2.second);
    }
    return (key2.first < data.key2.first);
  }
  return (key1 < data.key1);
}

