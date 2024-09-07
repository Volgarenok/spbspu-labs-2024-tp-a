#include "inputKey.hpp"
#include "delimiters.hpp"
#include "scopeGuard.hpp"

std::istream& basko::operator>>(std::istream& in, UllHexKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delChar = DelimiterChar;
  unsigned long long temp = 0;
  in >> delChar({ '0' }) >> delChar({ 'x' }) >> std::hex >> temp;
  if (in)
  {
    key.value = temp;
  }
  return in;
}

std::istream& basko::operator>>(std::istream& in, CmpLspKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delChar = DelimiterChar;
  using delString = DelimiterString;
  double real = 0.0;
  double imag = 0.0;
  in >> delString({ "#c(" }) >> real >> imag >> delChar{ { ')' } };
  if (in)
  {
    key.value = { real, imag };
  }
  return in;
}

std::istream& basko::operator>>(std::istream& in, StringKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delChar = DelimiterChar;
  std::string temp = "";
  in >> delChar({ '"' });
  std::getline(in, temp, '"');
  if (in)
  {
    key.value = temp;
  }
  return in;
}
