#include "inputKeys.hpp"
#include "Delimiter.hpp"

std::istream& sivkov::operator>>(std::istream& input, DoubleKey&& key)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }

  using del = DelimiterI;
  double num = 0;

  input >> num >> del{ 'd' };
  if (input)
  {
    key.num = num;
  }
  return input;
}

std::istream& sivkov::operator>>(std::istream& input, ComplexKey&& key)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }

  using del = DelimiterI;
  using delStr = DelimiterStr;
  double real = 0;
  double imag = 0;

  input >> delStr{ "#c(" } >> real >> imag >> del{ ')' };

  if (input)
  {
    key.num = { real, imag };
  }
  return input;
}

std::istream& sivkov::operator>>(std::istream& input, StringKey&& key)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }

  using del = DelimiterI;

  input >> del{ '"' };
  std::getline(input, key.string, '\"');
  return input;
}
