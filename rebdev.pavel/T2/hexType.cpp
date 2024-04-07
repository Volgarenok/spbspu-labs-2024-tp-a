#include "hexType.hpp"

#include "delimeter.hpp"
#include "streamGuard.hpp"

bool rebdev::hexType::operator==(const hexType & hex) const noexcept
{
  return data_ == hex.data_;
}

bool rebdev::hexType::operator<(const hexType & hex) const noexcept
{
  return data_ < hex.data_;
}

std::istream & rebdev::operator>>(std::istream & in, hexType & hex)
{
  hex.data_ = 0;
  std::istream::sentry sentryGuard(in);
  if(!sentryGuard)  return in;
  StreamGuard guard(in);

  in >> delimeter_t{'0'} >> delimeter_t{'x'} >> std::hex >> hex.data_;
  return in;
}

std::ostream & rebdev::operator<<(std::ostream & out, const hexType & hex)
{
  std::ostream::sentry sentryGuard(out);
  if (!sentryGuard) return out;
  StreamGuard guard(out);

  out << "0x" << std::uppercase << std::hex << hex.data_;

  return out;
}
