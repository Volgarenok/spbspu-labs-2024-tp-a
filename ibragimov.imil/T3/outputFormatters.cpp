#include "outputFormatters.hpp"

#include <iomanip>
#include <streamGuard.hpp>

std::ostream& ibragimov::operator<<(std::ostream& out, const AreaO&& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    detail::StreamGuard sguard(out);
    out << std::fixed << std::setprecision(1);
    out << value.ref;
  }
  return out;
}
