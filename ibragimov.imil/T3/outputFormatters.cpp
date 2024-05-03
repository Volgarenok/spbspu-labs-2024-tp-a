#include "outputFormatters.hpp"

#include <iomanip>
#include "../common/streamGuard.hpp"

std::ostream& ibragimov::operator<<(std::ostream& out, AreaO&& value)
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
