#include "formats.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& poleleyko::operator>>(std::istream& in, Litll&& num)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = StringDelimiter;
  StreamGuard s_guard(in);
  in >> num.value >> del{"ll"};
  return in;
}

std::istream& poleleyko::operator>>(std::istream& in, HexUll&& num)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = StringDelimiter;
  StreamGuard s_guard(in);
  in >> std::hex;
  in >> del{"0x"} >> num.value;
  return in;
}

std::istream& poleleyko::operator>>(std::istream& in, StringKey&& num)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = StringDelimiter;
  StreamGuard s_guard(in);
  in >> del{"\""};
  std::getline(in, num.str, '"');
  return in;
}