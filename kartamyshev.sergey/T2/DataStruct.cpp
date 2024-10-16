#include "DataStruct.h"
#include <iomanip>
#include <Delimiter.h>
#include "KeyType.h"

bool kartamyshev::DataStruct::operator<(const DataStruct& value) const
{
  if (key1 != value.key1)
  {
    return key1 < value.key1;
  }
  if (key2 != value.key2)
  {
    return key2 < value.key2;
  }
  return key3.length() < value.key3.length();
}

std::istream& kartamyshev::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delSym = DelimiterSym;
  using delStr = DelimiterStr;
  in >> delSym{ '(' };
  for (int i = 0; i < 3; i++)
  {
    int numberKey = 0;
    in >> delStr{ ":key" } >> numberKey;
    if (numberKey == 1)
    {
      in >> DoubleKey{ value.key1 };
    }
    else if (numberKey == 2)
    {
      in >> LLKey{ value.key2 };
    }
    else if (numberKey == 3)
    {
      in >> StrKey{ value.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> delStr{ ":)" };
  return in;
}

std::ostream& kartamyshev::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << std::setprecision(1);
  out << DoubleKeyOut{ value.key1 };
  out << ":key2 " << value.key2 << "ll";
  out << ":key3 \"" << value.key3 << "\":)";
  return out;
}

