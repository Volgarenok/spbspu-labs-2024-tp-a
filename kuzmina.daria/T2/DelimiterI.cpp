#include "DelimiterI.hpp"

#include <iomanip>

std::istream& kuzmina::operator>>(std::istream& in, DelimiterI&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  char c = 0;
  in >> c;
  if (std::tolower(c) != std::tolower(exp.expected))
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}
