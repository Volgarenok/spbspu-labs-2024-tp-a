#include "dataFormats.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& kozlov::operator>>(std::istream& in, UllHexVal&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard streamGuard(in);
  in >> std::hex;
  in >> DelimiterStr{"0x"} >> key.value;
  return in;
}

std::istream& kozlov::operator>>(std::istream& in, ChrLitVal&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> DelimiterChr{'\''} >> key.value >> DelimiterChr{'\''};
  return in;
}

std::istream& kozlov::operator>>(std::istream& in, StringVal&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> DelimiterChr{'"'};
  std::getline(in, key.value, '"');
  return in;
}
