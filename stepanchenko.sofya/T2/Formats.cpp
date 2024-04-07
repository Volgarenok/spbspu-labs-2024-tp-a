#include <iostream>
#include <string>

#include "Formats.hpp"
#include "Delimeter.h"


std::istream& stepanchenko::operator>>(std::istream& in, LongLongI&& ch)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    in.setstate(std::ios::failbit);
  }
  using strDel = StringDelimeterI;
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
  using del = DelimeterI;
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
  using del = DelimeterI;
  in >> del{ '\"' };
  std::getline(in, str.string_key, '"');
  in >> del{ '\"' };

  return in;
}
