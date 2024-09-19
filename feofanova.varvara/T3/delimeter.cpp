#include "delimeter.hpp"
#include <streamGuard.hpp>

#include <istream>

std::istream& feofanova::operator>>(std::istream& in, delimeter_t&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& feofanova::operator>>(std::istream& in, const IgnoreCaseDelimeter&& value)
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
