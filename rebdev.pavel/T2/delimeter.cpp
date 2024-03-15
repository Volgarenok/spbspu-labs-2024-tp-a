#include "delimeter.hpp"

#include <cctype>
std::istream & rebdev::operator >> (std::istream & in, delimeter && exp)
{

  std::istream::sentry guard(in);

  if (!guard) return in;

  char c = 0;
  in >> c;

  if (std::tolower(c) != std::tolower(exp.expectedChar))  in.setstate(std::ios::failbit);

  return in;
}
