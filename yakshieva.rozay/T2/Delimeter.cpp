#include "Delimeter.hpp"
#include "Streamguard.hpp"

std::istream& yakshieva::operator>>(std::istream& in, DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  Streamguard streamguard(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (c != dest.delimeter)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
