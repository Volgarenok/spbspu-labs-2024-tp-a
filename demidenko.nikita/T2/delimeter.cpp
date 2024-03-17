#include "delimeter.hpp"
#include <ios>
#include <istream>
#include "streamGuard.hpp"

std::istream& demidenko::operator>>(std::istream& in, DelimeterI&& del)
{
  demidenko::StreamGuard guard(in);
  in >> std::noskipws;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char current_character = ' ';
  while (in && *del.delimeter_)
  {
    in >> current_character;
    if (*del.delimeter_ != current_character)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    ++del.delimeter_;
  }
  return in;
}
