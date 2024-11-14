#include "delimiter.hpp"
#include <istream>

std::istream& skopchenko::operator>>(std::istream& in, delimiter_t&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (!exp.checkCase)
  {
    if (std::tolower(exp.expected) != std::tolower(exp.expected))
    {
      in.setstate(std::ios::failbit);
    }
  }
  else if (c != exp.expected)
  {
   in.setstate(std::ios::failbit);
  }
  return in;
}
skopchenko::delimiter_t::delimiter_t(char ex, bool check):
 expected(ex),
 checkCase(check)
{}
