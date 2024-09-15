#include "formats.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream & timchishina::operator>>(std::istream & in, SllLit && data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> data.key >> Delimiter{'l'} >> Delimiter{'l'};
  return in;
}

std::istream & timchishina::operator>>(std::istream & in, UllOct && data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard sGuard(in);
  in >> Delimiter{'0'} >> std::oct >> data.key;
  return in;
}

std::istream & timchishina::operator>>(std::istream & in, StringKey && data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::getline(in >> Delimiter{'\"'}, data.key, '\"');
  return in;
}
