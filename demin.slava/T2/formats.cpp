#include "dataFormats.hpp"
#include "formats.hpp"
#include "streamGuard.hpp"

std::istream &operator>>(std::istream &in, DblLit &&key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> key.value >> Delimiter{"d"};
  return in;
}

std::istream &operator>>(std::istream &in, UllOct &&key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard streamGuard(in);
  in >> Delimiter{"0"} >> std::oct >> oct;
  return in;
}

std::istream &operator>>(std::istream &in, StringVal &&key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::getline(in >> Delimiter{"\""}, str, '\"');
  return in;
}

