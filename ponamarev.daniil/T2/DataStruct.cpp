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

std::istream& ponamarev::operator>>(std::istream& in, DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  
  char c = '0';
  
  in >> c;
  
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  
  return in;
}

std::istream& ponamarev::operator>>(std::istream& in, UnsignedLongLongHexIO&& ull)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  
  return in >> DelimeterIO{ '0' } >> DelimeterIO{ 'x' } >> ull.ref >> DelimeterIO{':'};
}

std::istream& ponamarev::operator>>(std::istream& in, StringIO&& str)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  
  return std::getline(in >> DelimeterIO{ '"' }, str.ref, '"');
}

std::istream& ponamarev::operator>>(std::istream& in, LabelIO&& labe)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::string data = "";
  if ((in >> ponamarev::StringIO{ data }) && (data != labe.exp))
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream& ponamarev::operator>>(std::istream& in, RationalIO&& rat)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  return in >> DelimeterIO{ '(' } >> DelimeterIO{ ':' } >> DelimeterIO{ 'N' } >> rat.ref.first
    >> DelimeterIO{ ':' } >> DelimeterIO{ 'D' } >> rat.ref.second >> DelimeterIO{ ':' };
}
