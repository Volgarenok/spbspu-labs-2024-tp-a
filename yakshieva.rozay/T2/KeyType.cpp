#include "KeyType.hpp"
#include "Delimeter.hpp"
#include "Streamguard.hpp"

std::istream& yakshieva::operator>>(std::istream& in, DoubleIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double number;
  in >> number;
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
  return std::getline(in >> DelimeterIO{ '"' }, dest.ref, '"');
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
  in >> del{ '0' };
  char c;
  in >> c;
  c = std::tolower(c);
  if (c != 'b')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  char nextChar;
  in >> nextChar;
  if (nextChar == '1')
  {
    dest.value = 1;
    in.putback(nextChar);
  }
  in >> dest.value;
  return in;
}
