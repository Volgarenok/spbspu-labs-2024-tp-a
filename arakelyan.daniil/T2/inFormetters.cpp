#include "inFormatters.hpp"

#include <iostream>

#include <delimiter.hpp>
#include <formatGuard.hpp>

std::istream &arakelyan::operator>>(std::istream &in, OctUllIO &&dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  arakelyan::FormatGuard formG(in);
  in >> std::oct >> dest.ref;
  return in;
}

std::istream &arakelyan::operator>>(std::istream &in, CharLitIO &&dest)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  in >> DelimiterIO{'\''} >> dest.ref >> DelimiterIO{'\''};
  return in;
}

std::istream &arakelyan::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  return in;
}
