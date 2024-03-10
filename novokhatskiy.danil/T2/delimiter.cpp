#include "delimiter.hpp"

std::istream& novokhatskiy::operator>>(std::istream& in, Delimiter&& ex)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c{};
  in >> c;
  if (c != ex.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& novokhatskiy::operator>>(std::istream& in, DelimiterAlpha&& ex)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;
  c = std::tolower(c);
  if (c != ex.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& novokhatskiy::operator>>(std::istream& in, DelimiterString&& ex)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in;
}
