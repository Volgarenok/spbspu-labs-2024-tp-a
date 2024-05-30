#include "DataStruct.hpp"
#include <iostream>
#include <string>
#include <DelimiterI.hpp>
#include "KeyI.hpp"

bool kuzmina::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 == other.key1)
  {
    if (key2.first * other.key2.second == other.key2.first * key2.second)
    {
      return key3.size() < other.key3.size();
    }
    return key2.first * other.key2.second < other.key2.first * key2.second;
  }
  return key1 < other.key1;
}

std::istream& kuzmina::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  DataStruct temp{ 0, { 0, 0 }, "" };
  int keyX = 0;

  in >> DelimiterI{ '(' };
  for (std::size_t i = 0; i < 3; ++i)
  {
    in >> DelimiterIStr{ ":key" } >> keyX;

    if (keyX == 1)
    {
      in >> SLLKey{ temp.key1 };
    }

    else if (keyX == 2)
    {
      in >> RATKey{ temp.key2 };
    }

    else if (keyX == 3)
    {
      in >> STRKey{ temp.key3 };
    }

    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> DelimiterIStr{ ":)" };

  if (in)
  {
    value = temp;
  }

  return in;
}

std::ostream& kuzmina::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  out << "(:key1 " << value.key1 << "ll"
      << ":key2 (:N " << value.key2.first << ":D " << value.key2.second<< ":)"
      << ":key3 \"" << value.key3 << "\":)";

  return out;
}
