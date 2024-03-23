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
  using del = Delimeter;
  input >> del{'('} >> del{':'} >> DoubleFormat{dest.key1};
  input >> LongLongFormat{dest.key2};
  input >> StringFormat{dest.key3} >> del{')'};
  return input;
}

std::ostream & erohin::operator<<(std::ostream & output, const DataStruct & dest)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << "(:key1 " << dest.key1;
  output << ":key2 " << dest.key2;
  output << ":key3 \"" << dest.key3 << "\":)";
  return output;
}
