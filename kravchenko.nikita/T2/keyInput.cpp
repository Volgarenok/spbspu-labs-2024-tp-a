#include "keyInput.hpp"
#include <delimiterI.hpp>

std::istream& kravchenko::operator>>(std::istream& in, SignedLLKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  long long temp = 0;
  using sDel = kravchenko::StringDelimiterI< true >;
  in >> temp >> sDel{ "LL" };
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
  using cDel = kravchenko::DelimiterI< false >;
  using sDel = kravchenko::StringDelimiterI< false >;
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
  in >> kravchenko::DelimiterI< false >{ '"' };
  std::getline(in, key.value, '"');
  return in;
}
