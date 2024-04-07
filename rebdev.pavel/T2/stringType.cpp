#include "stringType.hpp"

#include <iomanip>

#include "delimeter.hpp"
#include "streamGuard.hpp"

bool rebdev::stringType::operator==(const stringType & str) const noexcept
{
  return data_ == str.data_;
}

bool rebdev::stringType::operator<(const stringType & str) const noexcept
{
  return data_ < str.data_;
}

std::istream & rebdev::operator>>(std::istream & in, stringType & str)
{
  str.data_ = "";
  std::istream::sentry sentryGuard(in);
  if(!sentryGuard)  return in;
  StreamGuard guard(in);

  in >> delimeter_t{'\"'};
  std::getline(in, str.data_, '\"');

  return in;
}

std::ostream & rebdev::operator<<(std::ostream & out, const stringType & str)
{
  std::ostream::sentry sentryGuard(out);
  if (!sentryGuard) return out;
  StreamGuard guard(out);

  out << std::quoted(str.data_, '\"');

  return out;
}
