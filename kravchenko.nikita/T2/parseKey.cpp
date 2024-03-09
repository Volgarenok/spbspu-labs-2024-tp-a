#include "parseKey.hpp"
#include "delimeterI.hpp"

void kravchenko::parseKey(std::istream& in, long long& value)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return;
  }
  long long temp = 0;
  using anySDel = kravchenko::AnyCaseStringDelimeterI;
  in >> temp >> anySDel{ "LL" };
  if (in)
  {
    value = temp;
  }
}

void kravchenko::parseKey(std::istream& in, std::complex< double >& value)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return;
  }
  using cDel = kravchenko::DelimeterI;
  double re = 0;
  double im = 0;
  in >> cDel{ '#' } >> cDel{ 'c' } >> cDel{ '(' } >> re >> im >> cDel{ ')' };
  if (in)
  {
    value = { re, im };
  }
}

void kravchenko::parseKey(std::istream& in, std::string& value)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return;
  }
  in >> kravchenko::DelimeterI{ '"' };
  std::getline(in, value, '"');
}
