#include "outputFormatters.hpp"
#include <iomanip>
#include <ios>

std::ostream& ibragimov::operator<<(std::ostream& out, const DoubleLitO&& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    out << std::showpoint << std::setprecision(2);
    out << value.ref << 'd';
    out << std::noshowpoint << std::setprecision(6);
  }
  return out;
}

std::ostream& ibragimov::operator<<(std::ostream& out, const ComplexLspO&& value)
{
  std::ostream::sentry guard(out);
  if (guard)
  {
    out << std::showpoint << std::setprecision(2);
    out << "#c" << '(' << value.ref.real() << ' ' << value.ref.imag() << ')';
    out << std::noshowpoint << std::setprecision(6);
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
