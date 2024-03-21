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
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << std::setprecision(1) << std::fixed;
  out << "(:key1 " << value.key1 << "D";
  out << ":key2 #c" << value.key2.real() << " " << value.key2.imag() << ":";
  out << "key3 \"" << value.key3 << "\":)";
  return out;
}

void enterKey(std::istream& in, size_t key, DataStruct& value)
{
  using del = DelimiterI;
  using delStr = DelimiterStr;
  if (key == 1)
  {
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
    in >> delStr{ "\"" };
    std::getline(in, value.key3, '"');
    in >> del{ ':' } >> del{ ')' };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
}
