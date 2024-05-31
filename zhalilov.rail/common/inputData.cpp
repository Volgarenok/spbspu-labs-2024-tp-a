#include "inputData.hpp"

#include <istream>
#include <cctype>
#include <cmath>

std::istream &zhalilov::operator>>(std::istream &in, DelimiterI &&symb)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  char temp = 0;
  in >> temp;
  if (std::tolower(temp) != symb.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &zhalilov::operator>>(std::istream &in, DoubleSciI &&dbl)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  double temp = 0.0;
  int power = 1;
  in >> MantissI{ temp } >> power;
  if (in)
  {
    dbl.num = temp * std::pow(10, power);
  }
  return in;
}

std::istream &zhalilov::operator>>(std::istream &in, MantissI &&mantiss)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }

  int power = -1;
  double mantissNum = 0.0;
  char temp = '0';
  bool hasNums = false;
  while ((in >> temp) && std::isdigit(temp))
  {
    hasNums = true;
    mantissNum *= 10;
    mantissNum += temp - '0';
  }
  if (temp == '.')
  {
    hasNums = true;
    while ((in >> temp) && std::isdigit(temp))
    {
      mantissNum += (temp - '0') * std::pow(10, power);
      power--;
    }
  }
  if (std::tolower(temp) == 'e' && hasNums)
  {
    mantiss.num = mantissNum;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &zhalilov::operator>>(std::istream &in, LongLongI &&ll)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }

  in >> ll.num >> DelimiterI{ 'l' } >> DelimiterI{ 'l' };
  return in;
}

std::istream &zhalilov::operator>>(std::istream &in, StringI &&str)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }

  return std::getline(in >> DelimiterI{ '"' }, str.text, '"');
}
