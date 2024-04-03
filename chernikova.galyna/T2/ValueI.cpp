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
  int mantissaFrac = 0;
  int exponent = 0;
  in >> mantissaInt >> DelimiterI{'.'} >> mantissaFrac >> DelimiterI{'e', true} >> exponent;
  std::cout << mantissaInt << ' ' << mantissaFrac << ' ' << exponent << ' ';
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
  std::cout << num << ' ';
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
  std::cout << dest.ref << ' ';
  return in;
}
