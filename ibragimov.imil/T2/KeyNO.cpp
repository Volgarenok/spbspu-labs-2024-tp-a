#include "keyNO.hpp"

#include <iostream>
#include "delimiter.hpp"

std::istream& ibragimov::operator>>(std::istream& in, KeyNO& value)
{
  using namespace ibragimov;
  std::istream::sentry guard(in);
  if (guard)
  {
    unsigned keyNo = 0;
    in >> Delimiter{'k'} >> Delimiter{'e'} >> Delimiter{'y'} >> keyNo;
    value.NO = keyNo;
  }
  return in;
}
