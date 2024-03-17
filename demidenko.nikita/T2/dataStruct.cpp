#include "dataStruct.hpp"
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include "dataStructBuilder.hpp"
#include "delimeter.hpp"
#include "streamGuard.hpp"

std::istream& demidenko::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  demidenko::StreamGuard guard(in);
  in >> std::setprecision(1) >> std::fixed >> std::noskipws;

  demidenko::DataStructBuilder builder(data);
  using del = demidenko::DelimeterI;
  using key = demidenko::KeyParser;
  using field = demidenko::FieldParser;

  in >> del{"(:"};
  for (int i = 0; i < 3; i++)
  {
    in >> key(builder) >> del{" "} >> field(builder) >> del{":"};
  }
  in >> del{")"};
  if (!builder.isDone())
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::ostream& demidenko::operator<<(std::ostream& out, DataStruct& data)
{
  return out;
}
