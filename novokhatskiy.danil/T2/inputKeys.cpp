#include "inputKeys.hpp"
#include <bitset>
#include <string>
#include "delimiter.hpp"

std::istream& novokhatskiy::operator>>(std::istream& in, BinKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    in.setstate(std::ios::failbit);
  }
  std::bitset< 64 > bin;
  in >> strictDel{ '0' } >> anyDel{ 'b' };
  in >> bin;
  if (in)
  {
    key.value = bin.to_ullong();
  }
  return in;
}

std::istream& novokhatskiy::operator>>(std::istream& in, RATKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    in.setstate(std::ios::failbit);
  }
  long long ll{};
  unsigned long long ull{};
  in >> anyStrD{ "(:n" } >> ll >> anyStrD{ ":d" } >> ull >> strictStrD{ ":)" };
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
  std::getline(in >> strictDel{ '"' }, tmp, '"');
  if (in)
  {
    key.str = tmp;
  }
  return in;
}
