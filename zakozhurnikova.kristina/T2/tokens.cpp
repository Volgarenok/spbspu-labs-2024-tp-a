#include "tokens.hpp"
#include <istream>
#include <scopeGuard.hpp>
#include <delimiter.hpp>

std::istream& zakozhurnikova::operator>>(std::istream& in, zakozhurnikova::DblLit&& data)
{
  std::istream::sentry guard(in);

  using delCh = DelimiterChar;

  if (!guard)
  {
    return in;
  }
  ScopeGuard scopeGuard(in);
  in >> data.key1 >> delCh{'d'};
  return in;
}

std::istream& zakozhurnikova::operator>>(std::istream& in, UllHex&& data)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }

  using delCh = DelimiterChar;
  ScopeGuard scopeGuard(in);
  in >> delCh{ '0' } >> delCh{ 'x' } >> std::hex >> data.key2;
  return in;
}

std::istream& zakozhurnikova::operator>>(std::istream& in, StringKey&& data)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }

  using delCh = DelimiterChar;
  in >> delCh{ '"' };
  std::getline(in, data.key3, '"');
  return in;
}
