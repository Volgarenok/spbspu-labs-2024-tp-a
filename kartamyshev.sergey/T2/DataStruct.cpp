#include "DataStruct.h"
#include <iomanip>
#include "Delimiter.h"

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
      in >> value.key1;
    }
    else if (numberKey == 2)
    {
      in >> value.key2 >> delSym{ 'l' } >> delSym{ 'l' };
    }
    else if (numberKey == 3)
    {
      in >> delStr({ "\"" });
      std::getline(in, value.key3, '"');
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
  out << "(:key1 " << std::setprecision(2) << value.key1;
  out << ":key2 " << value.key2 << "ll";
  out << ":key3 \"" << value.key3 << "\":)";
  return out;
}
