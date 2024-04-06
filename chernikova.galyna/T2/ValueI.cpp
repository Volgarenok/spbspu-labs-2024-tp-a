#include "ValueI.hpp"
#include <string>
#include <cmath>
#include "Delimiter.hpp"
#include "StreamGuard.hpp"

std::string chernikova::convertDblToSci(double num)
{
  int exponent = 0;

  while (std::abs(num) >= 10 || std::abs(num) < 1)
  {
    if (std::abs(num) >= 10)
    {
      num /= 10;
      ++exponent;
    }
    else
    {
      num *= 10;
      --exponent;
    }
  }

  int mantissa = static_cast<int>(std::round(num * 10));
  std::string result = std::to_string(mantissa);
  result.insert(1, 1, '.');
  result += 'e';
  if (exponent >= 0)
  {
    result += '+';
  }
  result += std::to_string(exponent);
  return result;
}

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
  if (in)
  {
    double mantissa = mantissaInt + mantissaFrac;
    dest.ref = mantissa * std::pow(10, exponent);
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
