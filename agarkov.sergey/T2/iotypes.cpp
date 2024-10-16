#include "iotypes.hpp"

std::istream& agarkov::operator>>(std::istream& in, DelimiterIO&& dest)
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
 
std::istream& agarkov::operator>>(std::istream& in, ComplexIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double real = 0.0;
  double imag = 0.0;
  in >> DelimiterIO{'#'} >> DelimiterIO{'c'} >> DelimiterIO{'('};
  in >> real >> imag >> DelimiterIO{')'};
  dest.cmp = std::complex< double >(real, imag);
  return in;
}
