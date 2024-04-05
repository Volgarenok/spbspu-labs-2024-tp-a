#include "delimiter.hpp"

#include <cstring>
#include <iostream>

std::istream &demin::operator>>(std::istream &in, DelimiterI &&exp)
{
  char c = 0;
  for (size_t i = 0; exp.exp[i] && in; ++i)
  {
    in >> c;
    if (c != exp.exp[i])
    {
      in.setstate(std::ios::failbit);
    }
  }

  return in;
}

std::istream &demin::operator>>(std::istream &in, InsensetiveDelimiterI &&exp)
{
  char c = 0;
  for (size_t i = 0; exp.exp[i] && in; ++i)
  {
    in >> c;
    if (std::tolower(c) != std::tolower(exp.exp[i]))
    {
      in.setstate(std::ios::failbit);
    }
  }

  return in;
}
