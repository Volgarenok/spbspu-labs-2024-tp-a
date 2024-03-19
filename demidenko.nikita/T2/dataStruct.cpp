#include "dataStruct.hpp"
#include <complex>
#include <iomanip>
#include <iostream>
#include "builder.hpp"
#include "delimeter.hpp"
#include "streamGuard.hpp"

bool demidenko::DataStruct::operator<(const DataStruct& other) const noexcept
{
  if (key1 < other.key1)
  {
    return true;
  }
  if (key1 > other.key1)
  {
    return false;
  }
  if (std::norm(key2) < std::norm(other.key2))
  {
    return true;
  }
  if (std::norm(key2) > std::norm(other.key2))
  {
    return false;
  }
  return key3.length() < other.key3.length();
}

std::istream& demidenko::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  DataStructBuilder builder(data);
  using del = DelimeterI;
  using key = KeyI;
  using field = FieldI;

  in >> del{ "(:" };
  for (int i = 0; i < 3; i++)
  {
    in >> key{ builder } >> del{ " " } >> field{ builder } >> del{ ":" };
  }
  in >> del{ ")" };
  if (!builder.isDone())
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& demidenko::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  StreamGuard guard(out);
  out << std::fixed << std::oct << std::setprecision(1);
  out << "(:key1 0" << data.key1;
  out << ":key2 #c(" << data.key2.real() << ' ' << data.key2.imag() << ')';
  out << ":key3 " << std::quoted(data.key3) << ":)";
  return out;
}
