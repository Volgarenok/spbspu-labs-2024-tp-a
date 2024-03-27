#include "inputKeys.hpp"
#include <bitset>
#include <istream>
#include <string>
#include "delimiter.hpp"


std::istream& novokhatskiy::operator>>(std::istream& in, BinKey&& key)
{
  using strD = novokhatskiy::DelimiterString;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    in.setstate(std::ios::failbit);
  }
  std::bitset< 64 > bin;
  in >> strD{ "0b" } >> bin;
  if (in)
  {
    key.value = bin.to_ullong();
  }
  return in;
}

std::istream& novokhatskiy::operator>>(std::istream& in, RATKey&& key)
{
  using strD = novokhatskiy::DelimiterString;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    in.setstate(std::ios::failbit);
  }
  long long ll{};
  unsigned long long ull{};
  in >> strD{ "(:n", true } >> ll >> strD{ ":d", true } >> ull >> strD{ ":)" };
  if (in)
  {
    key.pair.first = ll;
    key.pair.second = ull;
  }
  return in;
}

std::istream& novokhatskiy::operator>>(std::istream& in, STRKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    in.setstate(std::ios::failbit);
  }
  std::string tmp = "";
  std::getline(in >> Delimiter{ '"' }, tmp, '"');
  if (in)
  {
    key.str = tmp;
  }
  return in;
}
