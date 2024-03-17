#include "dataStruct.hpp"
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include "dataStructBuilder.hpp"
#include "delimeter.hpp"
#include "streamGuard.hpp"

std::istream& demidenko::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  demidenko::DataStructBuilder builder(data);
  using del = demidenko::DelimeterI;
  using key = demidenko::KeyParser;
  using field = demidenko::FieldParser;

  in >> del{"(:"};
  for (int i = 0; i < 3; i++)
  {
    in >> key{builder} >> del{" "} >> field{builder} >> del{":"};
  }
  in >> del{")"};
  if (!builder.isDone())
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& demidenko::operator<<(std::ostream& out, DataStruct& data)
{
  std::ostream::sentry sentry(out);
  demidenko::StreamGuard guard(out);
  out << std::fixed << std::oct << std::setprecision(1);
  out << "(:key1 0" << data.key1;
  out << ":key2 #c(" << data.key2.real() << ' ' << data.key2.imag() << ')';
  out << ":key3 " << std::quoted(data.key3) << ":)";
  return out;
}
