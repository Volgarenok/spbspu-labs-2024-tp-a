#include "valueO.hpp"
#include "formatGuard.hpp"

std::ostream& novikov::operator<<(std::ostream& out, const OctValueO& val)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  FormatGuard fmt_guard(out);
  out << std::oct;
  out << '0' << val.value;
  return out;
}

std::ostream& novikov::operator<<(std::ostream& out, const HexValueO& val)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  FormatGuard fmt_guard(out);
  out << std::hex << std::uppercase;
  out << "0x" << val.value;
  return out;
}

std::ostream& novikov::operator<<(std::ostream& out, const StrValueO& val)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '"' << val.value << '"';
  return out;
}
