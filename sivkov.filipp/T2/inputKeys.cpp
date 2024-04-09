#include "inputKeys.hpp"
#include "Delimiter.hpp"

std::istream& sivkov::operator>>(std::istream& input, DoubleKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return input;
  }

  using del = DelimiterI;
  using delStr = DelimiterStr;
  double num = 0;

  in >> num >> del{ 'd' };
  if (in)
  {
    key.num = num;
  }
  return input;
}

std::istream& sivkov::operator>>(std::istream& input, ComplexKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return input;
  }

  using del = DelimiterI;
  using delStr = DelimiterStr;
  double real = 0;
  double imag = 0;

  in >> delStr{ "#c(" } >> real >> imag >> del{ ')' };

  if (in)
  {
    key.num = { real, imag };
  }
  return input;
}

std::istream& sivkov::operator>>(std::istream& input, StringKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return input;
  }

  std::getline(in, key.string, '"');
  return input;
}

