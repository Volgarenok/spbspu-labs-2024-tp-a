#include "ValueI.h"
#include <string>
#include <cmath>
#include "Delimiter.h"

std::istream& chernikova::operator>>(std::istream& in, 
chernikova::DoubleI&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double mantissa = 0;
  int exponent = 0;
  char symbol = ' ';
  std::string strMantissa;
  std::string strExponent;

  while (!(in >> chernikova::DelimiterI{'e', true}))
  {
    in >> symbol;
    strMantissa += symbol;
    ++dest.ref;
  }
  while (in)
  {
    in >> symbol;
    strExponent += symbol;
    ++dest.ref;
  }

  mantissa = std::stod(strMantissa);
  exponent = std::stod(strExponent);
  dest.ref = mantissa * pow(10, exponent);
  return in;
}

int octalToDecimal(int octalNumber)
{
  int decimalNumber = 0;
  int i = 0;
  int rem = 0;
  while (octalNumber != 0)
  {
    rem = octalNumber % 10;
    octalNumber /= 10;
    decimalNumber += rem * pow(8, i);
    ++i;
  }
  return decimalNumber;
}

std::istream& chernikova::operator>>(std::istream& in, 
chernikova::UnsignedllI&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int num = 0;
  in >> num;
  exp.ref = octalToDecimal(num);
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, 
chernikova::StringI&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  while (*dest.ref != '\0')
  {
    in >> DelimiterI{*dest.ref};
    ++dest.ref;
  }
  return in;
}
