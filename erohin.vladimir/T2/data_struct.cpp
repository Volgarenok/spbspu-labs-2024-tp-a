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
  input >> Delimeter{'('} >> DoubleFormat{dest.key1};
  input >> LongLongFormat{dest.key2};
  input >> StringFormat{dest.key3} >> Delimeter{')'};
  return input;
}

std::ostream & erohin::operator<<(std::ostream & output, const DataStruct & dest)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << dest.key1 << "\n";
  output << dest.key2 << "\n";
  output << dest.key3 << "\n";
  return output;
}
