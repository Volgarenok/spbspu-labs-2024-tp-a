#include "dataStruct.hpp"
#include <iomanip>
#include "scopeGuard.hpp"

/*std::istream& grechishnikov::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = Delimiter;
}*/

std::ostream& grechishnikov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  ScopeGuard sGuard(out);

  out << std::oct <<"(:" << "key1 " << "0" << data.key1;
  out << ":" << "key2 " << "#c" << data.key2;
  out << ":" << "key3 " << "\"" << data.key3 << "\"" << ":)";
  return out;
}

std::ostream& grechishnikov::operator<<(std::ostream& out, const std::complex< double >& comp)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  ScopeGuard sGuard(out);

  out << std::fixed << std::setprecision(1) << "(" << comp.real() << " " << comp.imag() << ")";
  return out;
}
