#include "valueI.hpp"
#include "charDelimiterI.hpp"
#include "stringDelimiterI.hpp"
#include "formatGuard.hpp"

std::istream& novikov::operator>>(std::istream& in, OctValueI&& val)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    using chr_del = CharDelimiterI;
    FormatGuard fmt_guard(in);

    in >> chr_del{'0'};
    in >> std::oct;
    in >> val.value;
  }
  return in;
}

std::istream& novikov::operator>>(std::istream& in, HexValueI&& val)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    using str_del = StringDelimiterI;
    FormatGuard fmt_guard(in);
    in >> str_del{"0x", true};
    in >> std::hex;
    in >> val.value;
  }
  return in;
}

std::istream& novikov::operator>>(std::istream& in, StrValueI&& val)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    using chr_del = CharDelimiterI;
    FormatGuard fmt_guard(in);
    in >> chr_del{'"'};
    std::getline(in, val.value, '"');
  }
  return in;
}
