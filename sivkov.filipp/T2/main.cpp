#include <iostream>
#include <limits>
#include <string>
#include <complex>
#include <iomanip>
#include <iterator>
#include <list>
#include <algorithm>

struct DelimiterI
{
  char expected;
};

struct DelimiterStr
{
  const char * expected;
};

std::istream& operator>>(std::istream& in, DelimiterI&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  char c = 0;
  in >> c;

  if (in && std::tolower(c) != std::tolower(exp.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, DelimiterStr&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  for (size_t i = 0; exp.expected[i] != '\0'; ++i)
  {
    in >> DelimiterI{ exp.expected[i] };
  }
}

struct DataStruct
{
  double key1;
  std::complex<double> key2;
  std::string key3;
};

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
}

void enterKey(std::istream& in, size_t key, DataStruct& value)
{
  using del = DelimiterI;
  using delStr = DelimiterStr;
  if (key == 1)
  {
    double real = 0.0;
    double mnim = 0.0;
    in >> delStr{ "#c(" } >> real >> mnim >> del{ ')' };
    value.key2 = { real, mnim };
  }
  /*
  else if (key == 2)
  {

  }
  */
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

int main()
{
}
