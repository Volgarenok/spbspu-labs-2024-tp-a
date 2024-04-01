#include "delimiter.hpp"

std::istream &arakelyan::operator>>(std::istream &in, SeparIO &&exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.expSep)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}


std::istream &arakelyan::operator>>(std::istream &in, LableIO &&exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string expec = "";
  in >> expec;
  if (expec != exp.expLab)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}
