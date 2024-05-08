#include "key.hpp"
#include <istream>
#include <string>
#include <cmath>
#include "delimeter.hpp"

std::istream& spiridonov::operator>>(std::istream& in, DblSciI&& dbl)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double mantissa = 0.0;
  int power = 1;
  in >> MantissaI{ mantissa } >> power;
  if (in)
  {
    dbl.num = mantissa * std::pow(10, power);
  }
  return in;
}

std::istream& spiridonov::operator>>(std::istream& in, MantissaI&& mantissa)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double mantissaNum = 0.0;
  char current = '0';
  bool isCorrect = true;
  in >> current;
  if (std::isdigit(current))
  {
    mantissaNum += current - '0';
  }
  else
  {
    isCorrect = false;
  }
  in >> current;
  if (current != '.')
  {
    isCorrect = false;
  }
  int power = -1;
  while ((in >> current) && std::isdigit(current))
  {
    mantissaNum += (current - '0') * std::pow(10, power);
    power--;
  }
  if (std::tolower(current) == 'e' && isCorrect)
  {
    mantissa.mantissa = mantissaNum;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& spiridonov::operator>>(std::istream& in, StringI&& str)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::getline(in >> DelimeterChar{ '\"' }, str.value, '\"');
  return in;
}
