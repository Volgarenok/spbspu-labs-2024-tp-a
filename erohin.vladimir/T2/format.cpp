#include "format.hpp"
#include <iostream>
#include "delimeter.hpp"

std::istream & erohin::operator>>(std::istream & input, DoubleFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  return input >> dest.ref >> Delimeter{'d', false};
}

std::istream & erohin::operator>>(std::istream & input, LongLongFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  return input >> dest.ref >> Delimeter{'l', false} >> Delimeter{'l', false};
}

std::istream & erohin::operator>>(std::istream & input, StringFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  return std::getline(input >> Delimeter{'"'}, dest.ref, '"');
}
