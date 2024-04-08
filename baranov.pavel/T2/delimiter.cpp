#include "delimiter.hpp"

std::istream & baranov::operator>>(std::istream & in, Delimiter && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
