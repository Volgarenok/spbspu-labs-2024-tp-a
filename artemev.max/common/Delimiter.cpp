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

std::istream& artemev::operator>>(std::istream& in, const DelimiterStringI&& delimiter)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  for (size_t i = 0; delimiter.expected[i] != '\0'; ++i)
  {
    char c = {};
    in >> c;

    if (std::isalpha(c))
    {
      c = std::tolower(c);
    }

    if (c != delimiter.expected[i])
    {
      in.setstate(std::ios::failbit);
      break;
    }
  }
  return in;
}
