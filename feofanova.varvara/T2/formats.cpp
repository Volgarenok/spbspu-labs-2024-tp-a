#include "formats.hpp"
#include "streamGuard.hpp"
#include "Delimeter.hpp"

std::istream& feofanova::operator>>(std::istream& in, dbllit&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    in >> std::noskipws;
    in >> dest.value >> IgnoreCaseDelimeter{ "d" };
  }
  return in;
}

std::istream& feofanova::operator>>(std::istream& in, ullbin&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> delimeter_t{ '0' } >> delimeter_t{ 'b' };
  if (in)
  {
    char binary[64] = "";
    in.get(binary, 64, ':');
    for (size_t i = 0; binary[i] != '\0'; ++i)
    {
      if (!std::isdigit(binary[i]))
      {
        in.setstate(std::ios::failbit);
        return in;
      }
    }
    dest.value = std::stoull(binary, nullptr, 2);
  }
  return in;
}

std::istream& feofanova::operator>>(std::istream& in, String&& dest)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    StreamGuard sGuard(in);
    dest.str .clear();
    char c = '\0';
    in >> std::noskipws;
    using Delimeter = delimeter_t;
    in >> Delimeter{ '\"'};
    while ((in >> c) && (c != '"'))
    {
      if (c == '\\')
      {
        in >> c;
      }
      dest.str.push_back(c);
    }
  }
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
