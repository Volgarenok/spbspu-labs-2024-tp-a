#include "data_struct.hpp"
#include <string>
#include <cstring>
#include <delimiter.hpp>
#include <stream_guard.hpp>

bool zaitsev::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  if (key2 != other.key2)
  {
    return key2 < other.key2;
  }
  return key3.size() < other.key3.size();
}

std::istream& zaitsev::operator>>(std::istream& in, DataStruct& val)
{
  using delim = Delimiter;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  StreamGuard guard(in);

  in >> delim{ "(:" };
  int read_vals = 0;
  for (size_t i = 0; i < 3; ++i)
  {
    int nmb = 0;
    in >> delim{ "key" } >> nmb;
    switch (nmb)
    {
    case 1:
      in >> val.key1 >> delim{ "ull" } >> delim{ ":" };
      read_vals |= 0b1;
      break;
    case 2:
      in >> delim{ "0x" } >> std::hex >> val.key2 >> delim{ ":" };
      read_vals |= 0b10;
      break;
    case 3:
      std::getline(in >> delim{ "\"" }, val.key3, '\"') >> delim{ ":" };
      read_vals |= 0b100;
      break;
    default:
      in.setstate(std::ios::failbit);
    }
  }
  in >> delim{ ")" };

  if (read_vals ^ 0b111)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& zaitsev::operator<<(std::ostream& out, const DataStruct& val)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard guard(out);

  out << "(:key1 " << val.key1 << "ull";
  out << ":key2 0x" << std::hex << std::uppercase << val.key2;
  out << ":key3 \"" << std::nouppercase << val.key3 << "\":)";

  return out;
}
