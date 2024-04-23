#include "dataTypes.hpp"
#include <iostream>
#include "limiter.hpp"

std::istream & chistyakov::operator>>(std::istream & in, UllBinIO && data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Limiter{"0b"};

  std::string s = "";
  std::getline(in, s, ':');

  for (size_t i = 0; i < s.size(); ++i)
  {
    if (s[i] != '0' && s[i] != '1')
    {
      s.resize(i);
      break;
    }
  }

  data.value = std::stoull(s, 0, 2);
  return in;
}

std::ostream & chistyakov::operator<<(std::ostream & out, UllBinIO && data)
{
  unsigned long long tmp = data.value;
  char s[50]{};
  int index = 0;

  while (tmp > 0)
  {
    s[index] = tmp % 2;
    tmp /= 2;
    index++;
  }

  for (int i = index; i >= 0; i--)
  {
    out << s[i];
  }

  return out;
}

std::istream & chistyakov::operator>>(std::istream & in, RatLspIO && data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Limiter{"(:N"} >> data.value.first >> Limiter{":D"} >> data.value.second >> Limiter{":)"};
  return in;
}

std::istream & chistyakov::operator>>(std::istream & in, StringIO && data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Limiter{"\""};
  std::getline(in, data.value, '\"');
  return in;
}
