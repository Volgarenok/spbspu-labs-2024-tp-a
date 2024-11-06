#include "delimeter.hpp"

std::istream& felk::operator>>(std::istream& in, Delimeter&& del)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != del.exp || (!del.caseStrict && c != std::tolower(del.exp)))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& felk::operator>>(std::istream& in, WrapperLL&& del)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> del.data;
  in >> Delimeter{'l', false} >> Delimeter{'l', false};
  return in;
}

std::istream& felk::operator>>(std::istream& in, WrapperHex&& del)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> std::hex >> del.data >> std::dec;
  return in;
}

std::istream& felk::operator>>(std::istream& in, WrapperStr&& del)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> Delimeter{'\"'}, del.data, '\"');
}

felk::Delimeter::Delimeter(char exp, bool strict):
  exp(exp),
  caseStrict(strict)
{}
