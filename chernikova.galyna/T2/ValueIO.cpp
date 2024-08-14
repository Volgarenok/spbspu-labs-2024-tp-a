#include "ValueIO.hpp"
#include <string>
#include <cmath>
#include <delimiter.hpp>
#include <streamGuard.hpp>

std::string convertDblToSci(double num)
{
  int exponent = 0;
  bool flag = true;
  while (flag)
  {
    if (std::abs(num) >= 10)
    {
      num /= 10;
      ++exponent;
    }
    else if (std::abs(num) < 1)
    {
      num *= 10;
      --exponent;
    }
    else
    {
      flag = false;
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

std::ostream& chernikova::operator<<(std::ostream& out, const DoubleO&& exp)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << convertDblToSci(exp.ref);
  return out;
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
