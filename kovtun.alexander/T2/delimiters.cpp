#include "delimiters.hpp"


std::istream & kovtun::operator>>(std::istream &in, kovtun::KeyI && stub)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using dl = kovtun::DelimiterI;
  int num = 0;
  in >> dl{':'} >> dl{'k'} >> dl{'e'} >> dl{'y'} >> num;

  if (in)
  {
    stub.number = num;
  }

  return in;
}

std::istream & kovtun::operator>>(std::istream & in, kovtun::DoubleLitI && doubleLit)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  double d = 0.0;
  char c = 0;

  in >> d >> c;
  if (std::tolower(c) != 'd')
  {
    in.setstate(std::ios::failbit);
  }

  if (in)
  {
    doubleLit.dl = d;
  }

  return in;
}

std::istream & kovtun::operator>>(std::istream & in, kovtun::CharLitI && charLit)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  char c = 0;
  in >> DelimiterI{'\''} >> c >> DelimiterI{'\''};

  if (in)
  {
    charLit.cl = c;
  }

  return in;
}

std::istream & kovtun::operator>>(std::istream & in, kovtun::StringI && str)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> DelimiterI{'\"'};
  return std::getline(in, str.data, '\"');
}
