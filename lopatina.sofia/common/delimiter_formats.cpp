#include "delimiter_formats.hpp"

std::istream & lopatina::operator>>(std::istream & in, DelimiterIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  c = std::tolower(c);
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & lopatina::operator>>(std::istream & in, UllLiteralIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.ref >> DelimiterIO{'u'} >> DelimiterIO{'l'} >> DelimiterIO{'l'};
}

std::istream & lopatina::operator>>(std::istream & in, StringIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}
