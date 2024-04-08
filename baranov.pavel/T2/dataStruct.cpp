#include "dataStruct.hpp"
#include "dataStruct.hpp"

std::istream& baranov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  input.key3 = data.key3;
  return in;
}

