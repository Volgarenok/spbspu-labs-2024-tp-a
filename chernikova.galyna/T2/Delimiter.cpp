#include "Delimiter.h"
#include <iostream>
#include "ValueI.h"

std::istream& chernikova::operator>>(std::istream& in, 
chernikova::DelimiterI&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if ((!exp.variability) && (c != exp.expected) || exp.variability && 
(std::tolower(c) != std::tolower(exp.expected)))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

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
