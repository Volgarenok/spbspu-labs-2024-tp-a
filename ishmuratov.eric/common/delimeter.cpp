#include "delimeter.hpp"

std::istream & ishmuratov::operator>>(std::istream & in, Delimeter && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & ishmuratov::operator>>(std::istream &in, ishmuratov::DelimeterUll &&exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> exp.ref >> Delimeter{'u'} >> Delimeter{'l'} >> Delimeter{'l'};
  return in;
}

std::istream & ishmuratov::operator>>(std::istream &in, ishmuratov::DelimeterComplex &&exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Delimeter{'#'} >> Delimeter{'c'} >> Delimeter{'('};
  double real = 0.0;
  double imag = 0.0;
  in >> real >> imag;
  exp.ref.real(real);
  exp.ref.imag(imag);
  in >> Delimeter{')'};
  return in;
}

std::istream & ishmuratov::operator>>(std::istream &in, ishmuratov::DelimeterString &&exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Delimeter{'\"'};
  std::getline(in, exp.ref, '\"');
  return in;
}
