#include "ValueI.hpp"
#include <string>
#include <cmath>
#include "Delimiter.hpp"
#include "StreamGuard.hpp"

std::istream& chernikova::operator>>(std::istream& in, chernikova::DoubleI&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double mantissa = 0;
  int exponent = 0;
  char symbol = 0;
  std::string strMantissa;
  std::string strExponent;
  in >> symbol;
  while (symbol != DelimiterI{'e', true})
  {
    strMantissa += symbol;
    in >> symbol;
  }
  in >> DelimiterI{'e', true};
  while (in)
  {
    in >> symbol;
    strExponent += symbol;
  }
  mantissa = std::stod(strMantissa);
  exponent = std::stoi(strExponent);
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

std::istream& chernikova::operator>>(std::istream& in, chernikova::UnsignedllI&& exp)
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

std::istream& chernikova::operator>>(std::istream& in, chernikova::StringI&& dest)
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
