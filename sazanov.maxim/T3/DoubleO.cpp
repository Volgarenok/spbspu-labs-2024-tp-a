#include "DoubleO.hpp"
#include <iostream>
#include <iomanip>
#include <StreamGuard.hpp>

std::ostream& sazanov::operator<<(std::ostream& out, const DoubleO&& value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  StreamGuard guard(std::cout);
  std::cout << std::setprecision(1) << std::fixed;
  out << value.number;
  return out;
}
