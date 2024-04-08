#include "dataIO.hpp"

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

namespace serter
{
std::istream& operator>>(std::istream& in, DelimiterIO&& val)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char ch = 0;
  in >> ch;
  if (in && ch != std::tolower(val.val) && ch != std::toupper(val.val))
  {
    in.setstate(std::ios::failbit);
  }
  
  return in;
}

std::istream& operator>>(std::istream& in, StringIO&& val)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, val.val, '"');
}

std::istream& operator>>(std::istream& in, DoubleIO&& val)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  int mantissa = 0;
  int number = 0;
  int power = 0;
  in >> mantissa >> DelimiterIO{'.'} >> number >> DelimiterIO{'E'} >> power;
  val.val = (mantissa * 1.0 + number * 0.01) * std::pow(10, power);
  return in;
}

std::istream& operator>>(std::istream& in, UnsignedllIO&& val)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  unsigned long long number = 0;
  char c = 0;
  while (in >> c)
  {
    if (c == '0' || c == '1')
    {
      number = (number << 1) + (c - '0');
    }
    else
    {
      break;
    }
  }

  val.val = number;
  return in;
}

std::istream& operator>>(std::istream& in, LabelIO && val)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < val.val.length(); i++)
  {
    in >> DelimiterIO{val.val[i]};
  }
  return in;
}

std::string fromULLtoBinary(unsigned long long value)
{
  if (value == 0)
  {
    return "0";
  }
  
  std::string binary;
  while (value > 0)
  {
    binary.insert(0, std::to_string(value % 2));
    value /= 2;
  }
  return binary;
}

std::string fromDoubleToScientific(double val)
{
  int exp = 0;
  if (val == 0 || std::abs(val) == 1)
  {
    exp = 0;
  }
  else if (std::abs(val) < 1)
  {
    while (std::abs(val) * 10 < 10)
    {
      val *= 10;
      exp--;
    }
  }
  else
  {
    while (std::abs(val) / 10 >= 1)
    {
      val /= 10;
      exp++;
    }
  }
  std::string result = std::to_string(val) + (exp < 0 ? "e" : "e+") + std::to_string(std::abs(exp));
  return result;
}

}
