#include <iostream>

#include "inguard.hpp"
#include "delimiter.hpp"

std::istream &vojuck::operator>>(std::istream &in, DelimiterIO &&dest)
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

std::istream &vojuck::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream &vojuck::operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

std::istream &vojuck::operator>>(std::istream &in, HexULL &&dest)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  InGuard InGuard(in);
  in >> DelimiterIO{ '0' } >> DelimiterIO{ 'x' };
  in >> std::hex;
  in >> dest.ref;
  return in;
}

std::istream &vojuck::operator>>(std::istream &in, CharIO &&dest)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  in >> DelimiterIO{'\''} >> dest.ref >> DelimiterIO{'\''};
  return in;
}

