#include "delimiter.hpp"

std::istream& gladyshev::operator>>(std::istream& in, Delimiter&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  for (size_t i = 0; exp.exp[i] != '\0'; ++i)
  {
    in >> c;
    if (std::tolower(c) != exp.exp[i])
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
