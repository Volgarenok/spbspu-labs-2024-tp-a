#include "formats.hpp"
#include "streamGuard.hpp"
#include "Delimeter.hpp"

std::istream& feofanova::operator>>(std::istream& in, litI&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.value >> IgnoreCaseDelimeter{"d"};
}

std::istream& feofanova::operator>>(std::istream& in, binI&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using Delimeter = delimeter_t;
  in >> Delimeter{'0'}>>Delimeter{'b'} >> dest.value;
  return in;
}

std::istream& feofanova::operator>>(std::istream& in, StringI&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using Delimeter = delimeter_t;
  in >> Delimeter{ '\"' };
  std::getline(in, dest.str, '\"');
  return in;
}

std::ostream& feofanova::operator<<(std::ostream& out, unsigned long long src)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard s_guard(out);
  std::string binary = "";
  if (src)
  {
    binary = std::bitset<64>(src).to_string();
    binary.erase(0, binary.find_first_not_of('0'));
  }
  return out<< '0' + binary;;
}
