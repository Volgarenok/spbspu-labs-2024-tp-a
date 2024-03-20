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

int main()
{
}
