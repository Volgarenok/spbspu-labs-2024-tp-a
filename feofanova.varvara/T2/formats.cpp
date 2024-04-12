#include "formats.hpp"
#include "streamGuard.hpp"
#include "Delimeter.hpp"

std::istream& feofanova::operator>>(std::istream& in, dbllit&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.value >> IgnoreCaseDelimeter{ "d" };
}

std::istream& feofanova::operator>>(std::istream& in, ullbin&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using Delimeter = delimeter_t;
  in >> Delimeter{ '0b' } >> dest.value;
  return in;
}

std::istream& feofanova::operator>>(std::istream& in, String&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using Delimeter = delimeter_t;
  in >> Delimeter{ "\"" };
  std::getline(in, dest.value, '\"');
  return in;
}

std::string feofanova::toBinary(unsigned long long src)
{
    std::string binary = "";
    if (src)
    {
        binary = std::bitset<64>(src).to_string();
        binary.erase(0, binary.find_first_not_of('0'));
    }
    return '0' + binary;
}
