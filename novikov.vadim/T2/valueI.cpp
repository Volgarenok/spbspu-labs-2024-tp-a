#include "valueI.hpp"
#include "delimiterI.hpp"
#include "formatGuard.hpp"

std::istream& novikov::operator>>(std::istream& in, OctValueI&& val)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  FormatGuard fmt_guard(in);
  using chr_del = StrictCaseCharDelimiterI;
  in >> chr_del{ '0' };
  in >> std::oct;
  in >> val.value;
  return in;
}

std::istream& novikov::operator>>(std::istream& in, HexValueI&& val)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  FormatGuard fmt_guard(in);
  using str_del = IgnoreCaseStringDelimiterI;
  in >> str_del{ "0X" };
  in >> std::hex;
  in >> val.value;
  return in;
}

std::istream& novikov::operator>>(std::istream& in, StrValueI&& val)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  FormatGuard fmt_guard(in);
  using chr_del = StrictCaseCharDelimiterI;
  in >> chr_del{ '"' };
  std::getline(in, val.value, '"');
  return in;
}
