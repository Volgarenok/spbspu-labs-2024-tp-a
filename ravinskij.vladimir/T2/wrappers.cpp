#include "wrappers.hpp"
#include <string>
#include "delimeters.hpp"
#include "scopeGuard.hpp"

std::istream& ravinskij::operator>>(std::istream& in, BinUll&& data)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }
  using del = CharDelimeter;
  ScopeGuard scopeGuard(in);
  in >> del{'0'} >> del{'b'};
  in >> data.value;
  return in;
}

std::istream& ravinskij::operator>>(std::istream& in, HexUll&& data)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }

  using del = CharDelimeter;
  ScopeGuard scopeGuard(in);
  in >> del{'0'} >> del{'x'};
  in >> std::hex;
  in >> data.value;
  return in;
}

std::istream& ravinskij::operator>>(std::istream& in, StrKey&& data)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }

  using del = CharDelimeter;
  ScopeGuard scopeGuard(in);
  in >> del{ '"' };
  std::getline(in, data.value, '"');
  return in;
}
