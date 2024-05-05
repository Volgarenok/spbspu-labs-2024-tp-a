#include "formats.hpp"

#include <algorithm>
#include <cmath>

#include "delimiter.hpp"

std::istream& gladyshev::operator>>(std::istream& in, CharKey&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Delimiter{"'"} >> value.key >> Delimiter{"'"};
  return in;
}

std::istream& gladyshev::operator>>(std::istream& in, SciKey&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int mantissInt = 0;
  int mantissDiv = 0;
  int num = 0;
  in >> mantissInt >> Delimiter{"."} >> mantissDiv >> Delimiter{"e"} >> num;
  while (mantissDiv > 0)
  {
    mantissDiv /= 10;
  }
  value.key = (mantissInt + mantissDiv) * std::pow(10, num);
  return in;
}

std::istream& gladyshev::operator>>(std::istream& in, StrKey&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Delimiter{"\""};
  std::getline(in, value.key, '"');
  return in;
}
