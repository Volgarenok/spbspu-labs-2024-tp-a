#include "delimiters.hpp"

#include "streamGuard.hpp"

std::istream& ibragimov::operator>>(std::istream& in, const DelimiterI&& value)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    char c = '\0';
    in >> std::noskipws;
    for (size_t i = 0; value.expectation[i] != '\0'; ++i)
    {
      in >> c;
      if ((in) && (c != value.expectation[i]))
      {
        in.setstate(std::ios::failbit);
      }
    }
  }
  return in;
}

std::istream& ibragimov::operator>>(std::istream& in, const IgnoreCaseDelimiterI&& value)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    char c = '\0';
    in >> std::noskipws;
    for (size_t i = 0; value.expectation[i] != '\0'; ++i)
    {
      in >> c;
      if ((in) && (std::tolower(c) != std::tolower(value.expectation[i])))
      {
        in.setstate(std::ios::failbit);
      }
    }
  }
  return in;
}
