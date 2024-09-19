#include "delimiter.hpp"
#include <istream>

std::istream& zolotukhin::operator>>(std::istream& in, delimiter_t&& exp)
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
