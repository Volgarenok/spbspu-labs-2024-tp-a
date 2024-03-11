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
  if (std::isalpha(ex.expected) && std::tolower(c) != std::tolower(ex.expected))
  {
    in.setstate(std::ios::failbit);
  }
  else if (c != ex.expected)
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
  size_t i = 0;
  while (ex.expected[i] != '\0' && in)
  {
    in >> Delimiter{ ex.expected[i++] };
  }
  return in;
}

std::istream& novokhatskiy::operator>>(std::istream& in, DelimiterAlphaString&& ex)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t i = 0;
  while (ex.expected[i] && in)
  {
    in >> DelimiterAlpha{ ex.expected[i++] };
  }
  return in;
}
