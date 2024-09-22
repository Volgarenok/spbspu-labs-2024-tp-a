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
  using stub = kovtun::KeyI;

  double key1 = 0.0;
  char key2 = 0;

  int key = 0;

  in >> dl{'('} >> stub{key};
  if (key == 1)
  {
    in >> key1;
  }
  else if (key == 2)
  {
    in >> key2;
  }

  if (in)
  {
    data.key1 = key1;
    data.key2 = key2;
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
