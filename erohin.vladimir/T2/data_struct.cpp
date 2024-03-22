#include "data_struct.hpp"
#include <iostream>
#include "format.hpp"
#include "delimeter.hpp"

std::istream & erohin::operator>>(std::istream & input, DataStruct & dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  return input >> Delimeter{'('} >> dest.key1 >> Delimeter{')'};
}
