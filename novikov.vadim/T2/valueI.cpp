#include "valueI.hpp"
#include "charDelimiterI.hpp"
#include "stringDelimiterI.hpp"
#include "formatGuard.hpp"

std::istream& novikov::operator>>(std::istream& in, OctValueI&& exp)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    using chr_del = CharDelimiterI;
    FormatGuard fmt_guard(in);
    in >> chr_del{'0'};
    in >> std::oct;
    in >> exp.expected;
  }
  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const OctValueI& exp)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    FormatGuard fmt_guard(out);
    out << std::oct;
    out << '0' << exp.expected;
  }
  return out;
}

std::istream& novikov::operator>>(std::istream& in, HexValueI&& exp)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    using str_del = StringDelimiterI;
    FormatGuard fmt_guard(in);
    in >> str_del{"0x", true};
    in >> std::hex;
    in >> exp.expected;
  }
  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const HexValueI& exp)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    FormatGuard fmt_guard(out);
    out << std::hex << std::uppercase;
    out << "0x" << exp.expected;
  }
  return out;
}

std::istream& novikov::operator>>(std::istream& in, StrValueI&& exp)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    using chr_del = CharDelimiterI;
    FormatGuard fmt_guard(in);
    in >> chr_del{'"'};
    std::getline(exp.expected, '"');
    in >> chr_del{'"'};
  }
  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const StrValueI& exp)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << '"' << exp.expected << '"';
  }
  return out;
}
