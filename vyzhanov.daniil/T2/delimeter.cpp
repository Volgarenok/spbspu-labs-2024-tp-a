#include "delimetr.hpp"
#include <string>

std::istream& vyzhanov::operator>>(std::istream& input, Delimeter&& val)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  char c = 0;
  input >> c;
  if (c != val.expected)
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::istream& vyzhanov::operator>>(std::istream& input, DelimeterLit&& val)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  input >> val.ref >> Delimeter{ 'u' } >> Delimeter{ 'l' } >> Delimeter{ 'l' };
  return input;
}

std::istream& vyzhanov::operator>>(std::istream& input, DelimeterOct&& val)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  input >> Delimeter{ '0' };
  size_t key = 0;
  input >> std::oct >> key;
  if (!input)
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}
std::istream& vyzhanov::operator>>(std::istream& in, DelimeterString&& val)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Delimeter{ '\"' };
  std::getline(in, val.ref, '\"');
  return in;
}
