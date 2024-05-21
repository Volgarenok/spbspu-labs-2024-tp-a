#include "formats.hpp"
#include "streamGuard.hpp"
#include "Delimeter.hpp"

std::istream& feofanova::operator>>(std::istream& in, LitI&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.value >> IgnoreCaseDelimeter{"d"};
}

std::istream& feofanova::operator>>(std::istream& in, BinI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
        return in;
  }
  using Delimeter = Delimeter_i;
  in >> Delimeter{ '0' } >> Delimeter{ 'b' };
  if (in)
  {
    char binary[64]{};
    char c;
    size_t i = 0;
    while (in.get(c))
    {
      if (std::isdigit(c))
      {
        binary[i] = c;
        ++i;
      }
      else
      {
        in.putback(c);
        break;
      }
    }
    dest.value = std::stoull(binary, nullptr, 2);
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
  using Delimeter = Delimeter_i;
  in >> Delimeter{ '\"' };
  std::getline(in, dest.str, '\"');
  return in;
}

std::ostream& feofanova::operator<<(std::ostream& out, BinO&& src)
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
