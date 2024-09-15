#include "Key.hpp"
#include <Delimeter.hpp>

std::istream& kuznetsov::operator>>(std::istream& in, UllKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delstr = DelimeterString;
  unsigned long long num = 0;
  in >> num >> delstr{ "ull" };

  if (in)
  {
    key.data = num;
  }

  return in;
}

std::istream& kuznetsov::operator>>(std::istream& in, ComplexKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delchr = DelimeterChar;
  using delstr = DelimeterString;
  double real = 0;
  double imag = 0;
  in >> delstr{ "#c(" } >> real >> imag >> delchr{')'};

  if (in)
  {
    key.data = { real, imag };
  }

  return in;
}

std::istream& kuznetsov::operator>>(std::istream& in, StringKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delchr = DelimeterChar;
  in >> delchr{ '"' };
  std::getline(in, key.line, '"');

  return in;
}
