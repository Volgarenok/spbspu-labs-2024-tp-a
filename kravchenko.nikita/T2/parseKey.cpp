#include "parseKey.hpp"
#include "delimiterI.hpp"

std::istream& kravchenko::operator>>(std::istream& in, SignedLLKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  long long temp = 0;
  using sDel = kravchenko::StringDelimiterI;
  in >> temp >> sDel{ "LL", true };
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
  using cDel = kravchenko::DelimiterI;
  using sDel = kravchenko::StringDelimiterI;
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
  in >> kravchenko::DelimiterI{ '"' };
  std::getline(in, key.value, '"');
  return in;
}
