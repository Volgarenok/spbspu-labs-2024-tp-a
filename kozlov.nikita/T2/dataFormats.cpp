#include "dataFormats.hpp"
#include <inputCheck.hpp>
#include <streamGuard.hpp>

std::istream& kozlov::operator>>(std::istream& in, UllHexVal&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard streamGuard(in);
  in >> Label{"0x"} >> std::hex >> key.value;
  return in;
}

std::istream& kozlov::operator>>(std::istream& in, ChrLitVal&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Delimiter{'\''} >> key.value >> Delimiter{'\''};
  return in;
}

std::istream& kozlov::operator>>(std::istream& in, StringVal&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::getline(in >> Delimiter{'"'}, key.value, '"');
  return in;
}
