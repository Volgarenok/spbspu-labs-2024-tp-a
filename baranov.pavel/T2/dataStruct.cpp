#include "dataStruct.hpp"
#include <string>
#include <iomanip>
#include "delimiter.hpp"
#include "scopeGuard.hpp"

std::istream& baranov::operator>>(std::istream & in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' };
  DataStruct input{0, std::complex< double >(0, 0), ""};
  for (size_t i = 0; i < 3; ++i)
  {
    std::string label;
    in >> LabelIO{ label };
    if (label == "key1")
    {
      in >> HexUllIO{ input.key1 };
    }
    else if (label == "key2")
    {
      in >> ComplexIO{ input.key2 };
    }
    else if (label == "key3")
    {
      in >> StringIO{ input.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  data = input;
  return in;
}

std::ostream& baranov::operator<<(std::ostream & out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  ScopeGuard scopeGuard(out);
  out << '(';
  out << ":key1 0x" << std::hex << std::uppercase << data.key1;
  out << ":key2 #c" << std::fixed << std::setprecision(1) << '(' << data.key2.real() << ' ' << data.key2.imag() << ')';
  out << ":key3 \"" << data.key3 << '"';
  out << ')';
  return out;
}

