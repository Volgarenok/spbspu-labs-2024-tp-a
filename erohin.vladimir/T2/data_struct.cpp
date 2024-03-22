#include <iostream>

std::istream & erohin::operator>>(std::istream & input, DataStruct & dest)
{
  std::istream::sentry sentry;
  if (!sentry)
  {
    return input;
  }
  return input >> Delimeter{'('} >> Delimeter{')'};
}
