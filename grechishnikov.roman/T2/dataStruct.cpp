#include "dataStruct.hpp"

std::ostream& grechishnikov::operator<<(std::ostream& out, const std::complex< double >& comp)
{
  out << "(" << comp.real() << " " << comp.imag() << ")";
  return out;
}

std::ostream& grechishnikov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << std::oct <<"(:" << "key1 " << "0" << data.key1;
  out << ":" << "key2 " << "#c" << data.key2;
  out << ":" << "key3 " << "\"" << data.key3 << "\"" << ":)";
  return out;
}
