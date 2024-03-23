#include "data_struct.hpp"
#include <iostream>
#include "format.hpp"
#include "delimeter.hpp"
#include "scope_guard.hpp"

std::istream & erohin::operator>>(std::istream & input, DataStruct & dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  using del = Delimeter;
  using lbl = LabelFormat;
  input >> del{'('} >> del{':'} >> lbl{"key1"} >> DoubleFormat{dest.key1};
  input >> del{':'} >> lbl{"key2"} >> LongLongFormat{dest.key2};
  input >> del{':'} >> lbl{"key3"} >> StringFormat{dest.key3} >> del{':'} >> del{')'};
  return input;
}

std::ostream & erohin::operator<<(std::ostream & output, const DataStruct & dest)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  ScopeGuard sg(output);
  output << "(:key1 " << dest.key1;
  output << ":key2 " << dest.key2;
  output << ":key3 \"" << dest.key3 << "\":)";
  return output;
}
