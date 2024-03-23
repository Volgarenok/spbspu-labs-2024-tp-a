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
  DataStruct temp;
  input >> del{'('};
  input >> del{':'} >> lbl{"key1"} >> DoubleFormat{temp.key1};
  input >> del{':'} >> lbl{"key2"} >> LongLongFormat{temp.key2};
  input >> del{':'} >> lbl{"key3"} >> StringFormat{temp.key3};
  input >> del{':'} >> del{')'};
  if (input)
  {
    dest = temp;
  }
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
  output << std::fixed;
  output.precision(1);
  output << "(:key1 " << dest.key1 << 'd';
  output << ":key2 " << dest.key2 << "ll";
  output << ":key3 " << '"' << dest.key3 << '"' << ":)";
  return output;
}
