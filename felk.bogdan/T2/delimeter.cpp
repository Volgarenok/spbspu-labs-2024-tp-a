#include "delimeter.hpp"

std::istream& felk::operator>>(std::istream& in, Delimeter&& del)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != del.exp || !del.caseStrict && c != tolower(del.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

felk::Delimeter::Delimeter(char exp, bool strict) :
  exp(exp),
  caseStrict(strict)
{};
