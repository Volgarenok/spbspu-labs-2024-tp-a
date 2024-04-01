#include "inFormatters.hpp"
#include "delimiter.hpp"
#include "formatGuard.hpp"
#include <string>

std::istream &arakelyan::operator>>(std::istream &in, OctUll &&dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  arakelyan::FormatGuard formG(in);
  in >> dest.ref;
  return in;
}

std::istream &arakelyan::operator>>(std::istream &in, CharLit &&dest)
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
  in >> DelimiterIO{'"'};
  std::getline(in, dest.ref, '"');
  return in;
}
