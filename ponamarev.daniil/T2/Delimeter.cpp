#include "Delimeter.h"
#include "DataStruct.h"
#include "ioFormatGuard.h"
#include "Delimeter.h"
#include "DataStruct.h"
#include <string>
#include <iostream>

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
  return in >> DelimeterIO{ '0' } >> DelimeterIO{ 'x' } >> std::hex >> ull.ref >> DelimeterIO{':'};
}
std::istream& ponamarev::operator>>(std::istream& in, StringIO&& str)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimeterIO{ '"', str.ref, '"');
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
