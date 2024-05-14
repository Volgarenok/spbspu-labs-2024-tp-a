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
  unsigned long long num = data.value;
  int max_degree = -1;

  while (num > std::pow(2, max_degree))
  {
    max_degree++;
  }

  while (max_degree >= 0)
  {
    if (num >= std::pow(2, max_degree))
    {
      out << 1;
      num -= std::pow(2, max_degree);
      max_degree--;
    }
    else
    {
      out << 0;
      max_degree--;
    }
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
