#include "value.hpp"
#include <istream>
#include "scopeGuard.hpp"
#include "delimiter.hpp"

std::istream& kozlova::operator>>(std::istream& in, DblLitIO&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.key1 >> DelimiterCharIO{ 'd' };
}

std::istream& kozlova::operator>>(std::istream& in, RatLspFIO&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.firstKey2;
}

std::istream& kozlova::operator>>(std::istream& in, RatLspSIO&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.secondKey2;
}

std::istream& kozlova::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return std::getline(in >> DelimiterCharIO{ '"' }, dest.key3, '"');
}
