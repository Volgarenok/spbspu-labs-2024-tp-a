#include "outputFormatters.hpp"

#include <iomanip>
#include "streamGuard.hpp"

std::ostream& ibragimov::operator<<(std::ostream& out, const DoubleLitO&& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    ibragimov::StreamGuard sGuard(out);
    out << std::fixed << std::setprecision(1)
        << value.ref << 'd';
  }
  return out;
}

std::ostream& ibragimov::operator<<(std::ostream& out, const ComplexLspO&& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    ibragimov::StreamGuard sGuard(out);
    out << std::fixed << std::setprecision(1)
        << "#c" << '(' << value.ref.real() << ' ' << value.ref.imag() << ')';
  }
  return out;
}

std::ostream& ibragimov::operator<<(std::ostream& out, const StringO&& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    out << std::quoted(value.ref);
  }
  return out;
}
