#include "delimiter.hpp"
#include "scopeGuard.hpp"

std::istream & poleleyko::operator>>(std::istream & in, DelimiterIO && dest)
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

std::istream & poleleyko::operator>>(std::istream & in, LabelIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ ':' };
  in >> dest.ref;
  return in;
}

std::istream & poleleyko::operator>>(std::istream & in, StringIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream & poleleyko::operator>>(std::istream & in, HexUllIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  ScopeGuard scopeGuard(in);
  in >> DelimiterIO{ '0' } >> DelimiterIO{ 'x' };
  in >> std::hex;
  in >> dest.ref;
  return in;
}

std::istream & poleleyko::operator>>(std::istream & in, ComplexIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  ScopeGuard scopeGuard(in);
  in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' };
  double re = 0;
  double im = 0;
  in >> re >> im;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::complex< double > input(re, im);
  dest.ref = input;
  in >> DelimiterIO{ ')' };
  return in;
}