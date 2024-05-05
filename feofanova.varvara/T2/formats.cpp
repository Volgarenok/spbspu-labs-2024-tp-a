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
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    in >> DelimiterI{ '0' } >> DelimiterI{ 'b' };
    if (in)
    {
        char binary[64]{};
        for (size_t i = 0; std::isdigit(in.peek()); ++i)
        {
            in.get(binary[i]);
        }
        dest.ref = std::stoull(binary, nullptr, 2);
    }
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

std::ostream& feofanova::operator<<(std::ostream& out, binO&& src)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  std::string binary = "";
  if (src.value)
  {
    binary = std::bitset<64>(src.value).to_string();
    binary.erase(0, binary.find_first_not_of('0'));
  }
  return out << ('0' + binary);
}
