#include "nameOfKeys.hpp"
#include <delimiter.hpp>

std::istream& skuratov::operator>>(std::istream& in, UllKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = Delimiter;
  in >> del{ '0' } >> del{ 'x' } >> std::hex >> key.num;
  return in;
}

std::istream& skuratov::operator>>(std::istream& in, CharKey&& key)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = Delimiter;
  in >> del{ '\'' } >> key.num >> del{ '\'' };
  return in;
}

std::istream& skuratov::operator>>(std::istream& in, StringKey&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  in >> del{ '"' };
  std::getline(in, key.string, '"');
  return in;
}
