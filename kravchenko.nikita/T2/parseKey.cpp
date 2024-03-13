#include "parseKey.hpp"
#include "delimeterI.hpp"

std::istream& kravchenko::operator>>(std::istream& in, SignedLLKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  long long temp = 0;
  using anySDel = kravchenko::AnyCaseStringDelimeterI;
  in >> temp >> anySDel{ "LL" };
  if (in)
  {
    key.value = temp;
  }
  return in;
}

std::istream& kravchenko::operator>>(std::istream& in, ComplexKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using cDel = kravchenko::DelimeterI;
  using sDel = kravchenko::StringDelimeterI;
  double re = 0;
  double im = 0;
  in >> sDel{ "#c(" } >> re >> im >> cDel{ ')' };
  if (in)
  {
    key.value = { re, im };
  }
  return in;
}

std::istream& kravchenko::operator>>(std::istream& in, StringKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> kravchenko::DelimeterI{ '"' };
  std::getline(in, key.value, '"');
  return in;
}
