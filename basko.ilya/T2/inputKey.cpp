#include "inputKey.hpp"
#include "delimiters.hpp"
#include "scopeGuard.hpp"

std::istream& basko::operator>>(std::istream& in, UllHexKey&& data)
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
    data.key1 = temp;
  }
  return in;
}

std::istream& basko::operator>>(std::istream& in, CmpLspKey&& data)
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
    data.key2 = { real, imag };
  }
  return in;
}

std::istream& basko::operator>>(std::istream& in, StringKey&& data)
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
    data.key3 = temp;
  }
  return in;
}
