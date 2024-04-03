#include "ValueI.hpp"
#include <string>
#include <cmath>
#include "Delimiter.hpp"
#include "StreamGuard.hpp"

std::istream& chernikova::operator>>(std::istream& in, DoubleI&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int mantissaInt = 0;
  double mantissaFrac = 0;
  int exponent = 0;
  in >> mantissaInt >> mantissaFrac >> DelimiterI{'e', true} >> exponent;
  if (in)
  {
    double mantissa = mantissaInt + mantissaFrac;
    dest.ref = mantissa * pow(10, exponent);
  }
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, UnsignedllI&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int num = 0;
  in >> DelimiterI{'0'} >> std::oct >> num;
  exp.ref = num;
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, StringI&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard streamGuard(in);
  in >> DelimiterI{'"'};
  std::getline(in, dest.ref, '"');
  return in;
}
