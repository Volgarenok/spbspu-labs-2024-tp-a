#include "delimiter.hpp"
#include "inFormatters.hpp"

std::istream &arakelyan::operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &arakelyan::operator>>(std::istream &in, LableIO &&dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string expec = "";
  in >> expec;
  if (expec != dest.exp)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}
