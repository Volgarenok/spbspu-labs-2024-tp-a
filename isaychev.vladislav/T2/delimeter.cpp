#include "delimeter.hpp"
#include <iostream>

std::istream & isaychev::operator>>(std::istream & in, delim_ch_t && sym)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != sym.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & isaychev::operator>>(std::istream & in, delim_str_t && seq)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  bool isRight = true;
  for (int i = 0; seq.exp[i] != '\0'; ++i)
  {
    in >> c;
    if (seq.exp[i] != c)
    {
      isRight = false;
    }
  }
  if (!isRight)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

