#include "Keys.h"
#include "Delimiter.h"



std::istream& kazennov::operator>>(std::istream& in, CharKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using Del = Delimiter;
  char sym;

  in >> Del{'\''} >> sym >> Del{'\''};
  if (in)
  {
    key.c = sym;
  }
  return in;
}
std::istream& kazennov::operator>>(std::istream& in, RatKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using StrDel = StringDelimiter;

  long long n = 0;
  unsigned long long d = 0;
  in >> StrDel{"(:N"} >> n >> StrDel{":D"} >> d >> StrDel{":)"};
  if (in)
  {
    key.rat.first = n;
    key.rat.second = d;
  }
  return in;
}
std::istream& kazennov::operator>>(std::istream& in, StrKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using Del = Delimiter;

  in >> Del{ '"' };
  std::getline(in, key.str, '\"');
  return in;
}

