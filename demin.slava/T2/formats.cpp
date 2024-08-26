#include "formats.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream &demin::operator>>(std::istream &in, DblLit &&key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = demin::Delimiter;
  in >> key.value >> del{"d"};
  return in;
}

std::istream &demin::operator>>(std::istream &in, UllOct &&key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  demin::StreamGuard streamGuard(in);
  using del = demin::Delimiter;
  in >> del{"0"} >> std::oct >> key.value;
  return in;
}

std::istream &demin::operator>>(std::istream &in, StringVal &&key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = demin::Delimiter;
  std::getline(in >> del{"\""}, key.value, '\"');
  return in;
}

