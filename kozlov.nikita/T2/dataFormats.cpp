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
  in >> DelimiterStr{"0x"} >> std::hex >> key.value;
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
  std::getline(in >> DelimiterChr{'"'}, key.value, '"');
  return in;
}
