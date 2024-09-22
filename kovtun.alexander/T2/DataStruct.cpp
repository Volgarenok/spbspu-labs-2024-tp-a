#include "DataStruct.hpp"

std::istream & kovtun::operator>>(std::istream & in, kovtun::DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  kovtun::IOScopeGuard scopeGuard(in);

  using dl = kovtun::DelimiterI;

  double d = 0.0;
  char c = 0;

  int key = 0;

  in >> dl{'('} >> dl{':'} >> dl{'k'} >> dl{'e'} >> dl{'y'} >> key;
  if (key == 1)
  {
    in >> d;
  }
  else if (key == 2)
  {
    in >> c;
  }

  if (in)
  {
    data.key1 = d;
    data.key2 = c;
  }

  return in;
}

std::ostream & kovtun::operator<<(std::ostream & out, const kovtun::DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  kovtun::IOScopeGuard scopeGuard(out);

  std::cout << data.key1;

  return out;
}
