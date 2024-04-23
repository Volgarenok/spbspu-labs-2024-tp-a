#include "KeyType.hpp"
#include "Delimeter.hpp"
#include "Streamguard.hpp"

std::ostream& yakshieva::ScienConversion(std::ostream& out, double num)
{
  int exponent = 0;
  double mantissa = num;
  if (mantissa != 0)
  {
    if (mantissa >= 1.0 && mantissa < 10.0)
    {
      out << std::fixed << mantissa;
    }
    else if (mantissa >= 10.0)
    {
      while (mantissa >= 10.0)
      {
        mantissa = mantissa / 10;
        exponent++;
      }
      out << std::fixed << mantissa << 'e' << '+' << exponent;
    }
    else if (mantissa < 1.0)
    {
      while (mantissa < 1.0)
      {
        mantissa = mantissa * 10;
        exponent--;
      }
      out << std::fixed << mantissa << 'e' << exponent;
    }
  }
  else
  {
    out << std::fixed << mantissa;
  }
  return out;
}

std::istream& yakshieva::operator>>(std::istream& in, DoubleIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double number = 0;
  if (!(in >> number))
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.ref = number;
  return in;
}

std::istream& yakshieva::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::getline(in >> DelimeterIO{ '"' }, dest.ref, '"');
  if (!in.eof() && !in)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& yakshieva::operator>>(std::istream& in, BinaryIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Streamguard fmtguard(in);
  using del = DelimeterIO;
  char c = '0';
  in >> del{ '0' } >> c;
  if (in && std::tolower(c) != 'b')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> dest.value;
  if (!in && dest.value != 0 && dest.value != 1)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
