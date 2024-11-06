#include "value.hpp"
#include <istream>
#include <scopeGuard.hpp>
#include <delimiter.hpp>

std::istream & kozlova::operator>>(std::istream & in, DblLitIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.dbllit_key >> DelimiterCharIO{ 'd' };
}

std::istream & kozlova::operator>>(std::istream & in, RatLspFIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.ratlspf_key;
}

std::istream & kozlova::operator>>(std::istream & in, RatLspSIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.ratlsps_key;
}

std::istream & kozlova::operator>>(std::istream & in, StringIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return std::getline(in >> DelimiterCharIO{ '"' }, dest.string_key, '"');
}
