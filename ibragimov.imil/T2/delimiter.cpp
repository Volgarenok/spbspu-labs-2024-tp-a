#include "delimiter.hpp"
#include <string>

std::istream& ibragimov::operator>>(std::istream& in, DelimiterI&& expectation)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    char c = '0';
    in >> c;
    if (in && (c != expectation.expected))
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::istream& ibragimov::operator>>(std::istream& in, StringI&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    std::getline(in >> DelimiterI{'"'}, dest.ref, '"');
  }
  return in;
}
