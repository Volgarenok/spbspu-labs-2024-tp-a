#include "KeysIn.hpp"
#include "Delimiters.hpp"
#include "StreamGuard.hpp"

std::istream& kozakova::operator>>(std::istream& in, KeyUll&& v)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using dels = kozakova::DelimiterString;
  unsigned long long a = 0;
  in >> a >> dels{ "ULL" };
  if (in)
  {
    v.value = a;
  }
  return in;
}

std::istream& kozakova::operator>>(std::istream& in, KeyHex&& v)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delc = kozakova::DelimiterChar;
  unsigned long long b = 0;
  kozakova::StreamGuard sguard(in);
  in >> delc{ '0' } >> delc{ 'X' } >> std::hex >> b;
  if (in)
  {
    v.value = b;
  }
  return in;
}

std::istream& kozakova::operator>>(std::istream& in, KeyString&& v)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delc = kozakova::DelimiterChar;
  std::string s = "";
  in >> delc{ '"' };
  std::getline(in, s, '"');
  if (in)
  {
    v.value = s;
  }
  return in;
}
