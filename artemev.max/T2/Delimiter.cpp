#include "Delimiter.hpp"

#include <cctype>
#include <ios>

std::istream& artemev::operator>>(std::istream& in, const DelimiterCharI&& delimiter)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  char c = 0;
  in >> c;

  if (std::isalpha(c))
  {
    c = std::tolower(c);
  }

  if (c != delimiter.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
