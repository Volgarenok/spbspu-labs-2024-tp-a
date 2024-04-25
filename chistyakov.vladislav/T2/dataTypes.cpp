#include "dataTypes.hpp"
#include <iostream>
#include <cmath>
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

  unsigned long long result = 0;
  int degree = -1;

  for (size_t i = 0; i < s.size(); i++)
  {
    if (s[s.size() - i] == '1')
    {
      result += std::pow(2, degree);
      degree++;
    }
    else
    {
      degree++;
    }
  }

  data.value = result;

  return in;
}

std::ostream & chistyakov::operator<<(std::ostream & out, UllBinIO && data)
{
  unsigned long long tmp = data.value;
  std::string s = "";
  int index = 0;

  while (tmp > 0)
  {
    s += tmp % 2;
    tmp /= 2;
    index++;
  }

  for (auto i = s.end(); i != s.begin(); i--)
  {
    std::cout << *i;
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
