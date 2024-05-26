#include "formats.hpp"

#include <algorithm>
#include <cmath>

#include <delimiter.hpp>

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
  int divDigits = 0;
  int temp = mantissDiv;
  while (temp > 0)
  {
    temp /= 10;
    divDigits++;
  }
  double mantiss = mantissInt + mantissDiv / std::pow(10, divDigits);
  value.key = mantiss * std::pow(10, num);
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
