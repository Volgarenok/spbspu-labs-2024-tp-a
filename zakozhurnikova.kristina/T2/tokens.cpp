#include "tokens.hpp"
#include <istream>
#include <scopeGuard.hpp>
#include <delimiter.hpp>

std::istream& zakozhurnikova::operator>>(std::istream& in, zakozhurnikova::DblLit&& data)
{
  std::istream::sentry guard(in);

  using del = Delimiter;

  if (!guard)
  {
    return in;
  }
  ScopeGuard scopeGuard(in);
  in >> data.key1 >> del{"d"};
  return in;
}

std::istream& zakozhurnikova::operator>>(std::istream& in, UllHex&& data)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }

  using del = Delimiter;
  ScopeGuard scopeGuard(in);
  in >> del{ "0" } >> del{ "x" } >> std::hex >> data.key2;
  return in;
}

std::istream& zakozhurnikova::operator>>(std::istream& in, StringKey&& data)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }

  using del = Delimiter;
  in >> del{ "\"" };
  std::getline(in, data.key3, '"');
  return in;
}
