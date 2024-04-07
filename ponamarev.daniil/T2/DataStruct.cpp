#include "DataStruct.h"
#include "Delimeter.h"
#include "ioFormatGuard.h"
#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>
#include <iostream>

std::istream& ponamarev::operator>>(std::istream& in, DataStruct& obj)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimeterIO;
    using label = LabelIO;
    using ull = UnsignedLongLongHexIO;
    using str = StringIO;
    using rat = RationalIO;
    in >> sep{ '(' };
    in >> sep{ ':' };
    in >> label{ "key1" } >> sep{ ' ' } >> ull{ input.key1 };
    in >> sep{ ':' };
    in >> label{ "key2" } >> sep{ ' ' } >> rat{ input.key2 };
    in >> sep{ ':' };
    in >> label{ "key3" } >> sep{ ' ' } >> str{ input.key3 };
    in >> sep{ ':' };
    in >> sep{ ')' };
  }
  if (in)
  {
    obj = input;
  }
  return in;
}
