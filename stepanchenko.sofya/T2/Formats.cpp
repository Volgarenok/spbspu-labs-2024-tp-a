#include "Formats.hpp"

#include <iostream>
#include <string>

#include "Delimiters.hpp"

std::istream& stepanchenko::operator>>(std::istream& in, LongLongI&& ch)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    in.setstate(std::ios::failbit);
  }
  using strDel = StringDelimiterI;
  in >> ch.longlong_key >> strDel{ "ull" };

  return in;
}


std::istream& stepanchenko::operator>>(std::istream& in, CharI&& ch)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    in.setstate(std::ios::failbit);
  }
  using del = DelimiterI;
  in >> del{ '\'' } >> ch.char_key >> del{ '\'' };

  return in;
}


std::istream& stepanchenko::operator>>(std::istream& in, StringI&& str)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    in.setstate(std::ios::failbit);
  }
  using del = DelimiterI;
  in >> del{ '\"' };
  std::getline(in, str.string_key, '"');

  return in;
}
