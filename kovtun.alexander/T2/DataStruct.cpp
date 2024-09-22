#include "DataStruct.hpp"

std::istream & kovtun::operator>>(std::istream & in, kovtun::DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  kovtun::IOScopeGuard scopeGuard(in);

  using del = kovtun::DelimiterI;
  double d = 0.0f;
  in >> del{'['} >> d >> del{']'};
  if (in)
  {
    data.key1 = d;
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
