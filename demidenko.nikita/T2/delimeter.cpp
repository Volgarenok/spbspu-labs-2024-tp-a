#include "delimeter.hpp"
#include <istream>
#include "streamGuard.hpp"

std::istream& demidenko::operator>>(std::istream& in, DelimeterI&& del)
{
  StreamGuard guard(in);
  in >> std::noskipws;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char current_character = ' ';
  const char* delimeter = del.delimeter;
  while (in && *delimeter)
  {
    in >> current_character;
    if (*delimeter != current_character)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    ++delimeter;
  }
  return in;
}
