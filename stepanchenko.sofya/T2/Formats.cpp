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
