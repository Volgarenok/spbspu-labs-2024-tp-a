#include "DataStruct.hpp"
#include <iomanip>
#include "Delimiter.hpp"

std::istream& operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterI;
  using delStr = DelimiterStr;
  size_t numOfKey = 0;
  in >> del{ '(' };
  for (size_t i = 0; i != 3; i++)
  {
    in >> del{ ':' } >> delStr{ "key" } >> numOfKey;
    enterKey(in, numOfKey, value);
  }
  in >> delStr{ ":)" };
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    return out;
  }
  out << std::setprecision(1) << std::fixed;
  out << '(';
  out << ":key1 " << '\'' << value.key1 << '\'';
  return out;
}

void enterKey(std::istream& in, size_t key, DataStruct& value)
{
  using del = DelimiterI;
  using delStr = DelimiterStr;
  if (key == 1)
  {
    double num = 0.0;
    in >> value.key1 >> del{ 'd' };
  }
  else if (key == 2)
  {
    double real = 0.0;
    double mnim = 0.0;
    in >> delStr{ "#c(" } >> real >> mnim >> del{ ')' };
    value.key2 = { real, mnim };
  }
  else if (key == 3)
  {
    in >> delStr{ " \"" };
    in >> value.key3;
    in >> del{ ':' };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
}

