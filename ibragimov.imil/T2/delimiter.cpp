#include "delimiter.hpp"

std::istream& ibragimov::operator>>(std::istream& in, Delimiter&& expectation)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    char c = 0;
    in >> c;
    if (c != expectation.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
