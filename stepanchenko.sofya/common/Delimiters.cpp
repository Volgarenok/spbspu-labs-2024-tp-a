<<<<<<< HEAD:stepanchenko.sofya/common/Delimiters.cpp
#include <cstring>

#include "Delimiters.hpp"
=======
#include "Delimiters.hpp"
>>>>>>> master:stepanchenko.sofya/T2/Delimiters.cpp

#include <cstring>

std::istream& stepanchenko::operator>>(std::istream& in, DelimiterI&& del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = ' ';
  in >> c;
  if (std::isalpha(c))
  {
    c = std::tolower(c);
  }
  if (c != del.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& stepanchenko::operator>>(std::istream& in, StringDelimiterI&& del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  for (size_t i = 0; del.expected[i] && in; ++i)
  {
    char c = ' ';
    in >> c;
    c = std::tolower(c);
    if (c != del.expected[i])
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
