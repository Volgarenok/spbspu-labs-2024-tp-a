#include "delimiters.hpp"
#include "streamGuard.hpp"
#include <iostream>
#include <cmath>

std::istream& chernov::operator>>(std::istream& in, UnsignedLongLongIO&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> CharIO{ '0' } >> CharIO{ 'x' } >> std::hex >> exp.value_;
}

std::istream& chernov::operator>>(std::istream& in, CharIO&& exp)
{}

std::istream& chernov::operator>>(std::istream& in, DoubleIO&& exp)
{}

std::istream& chernov::operator>>(std::istream& in, StringIO&& exp)
{}

std::string chernov::convertDoubleToCalcDouble(double number)
{}
