#include "Delimiter.h"
#include <iostream>
#include "ValueI.h"

std::istream& chernikova::operator>>(std::istream &in, 
chernikova::StringDelimiterI &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char* data = nullptr;
  if ((in >> chernikova::StringI{data}) && (data != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

