#include <delimeters.hpp>
#include <cctype>

std::istream& ravinskij::operator>>(std::istream& in, CharDelimeter&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  char c = 0;
  in >> c;
  if ((c != exp.expected) && (std::tolower(c) != std::tolower(exp.expected)))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
