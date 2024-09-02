#include "KeyType.hpp"
#include <Delimeter.hpp>
#include <StreamGuard.hpp>

std::istream& yakshieva::operator>>(std::istream& in, DoubleIn&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double number = 0.0;
  in >> number;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.ref = number;
  return in;
}

std::string scienConversion(double num)
{
  int exponent = 0;
  double mantissa = std::abs(num);
  if (mantissa != 0.0)
  {
    if (mantissa >= 10.0)
    {
      while (mantissa >= 10.0)
      {
        mantissa = mantissa / 10;
        exponent++;
      }
    }
    else if (mantissa < 1.0)
    {
      while (mantissa < 1.0)
      {
        mantissa = mantissa * 10;
        exponent--;
      }
    }
  }
  else
  {
    return "0.0";
  }
  std::string mantissaStr = std::to_string(mantissa);
  size_t dotPos = mantissaStr.find('.');
  if (dotPos != std::string::npos && mantissaStr.length() > dotPos + 2)
  {
    mantissaStr = mantissaStr.substr(0, dotPos + 2);
  }
  std::string result = mantissaStr + "e";
  if (exponent >= 0)
  {
    result += '+';
  }
  result += std::to_string(exponent);
  return result;
}

std::ostream& yakshieva::operator<<(std::ostream& out, const DoubleOut&& exp)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << scienConversion(exp.ref);
  return out;
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
  StreamGuard fmtguard(in);
  using del = DelimeterIO;
  in >> del{ '0' } >> del{ 'b' };
  dest.value = 0;
  in >> dest.value;
  if (in && dest.value != 0 && dest.value != 1)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
