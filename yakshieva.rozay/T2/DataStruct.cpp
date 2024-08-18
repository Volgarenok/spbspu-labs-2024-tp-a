#include "DataStruct.hpp"
#include <iomanip>
#include <string>
#include <Delimeter.hpp>
#include "KeyType.hpp"
#include <StreamGuard.hpp>

bool yakshieva::DataStruct::operator<(const DataStruct& data) const
{
  if (key1 == data.key1)
  {
    if (key2 == data.key2)
    {
      return key3.length() < data.key3.length();
    }
    return key2 < data.key2;
  }
  return key1 < data.key1;
}

std::istream& yakshieva::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input {};
  using sep = DelimeterIO;
  using dbl = DoubleIn;
  using str = StringIO;
  using bin = BinaryIO;
  in >> sep{ '(' };
  if (!in)
  {
    return in;
  }
  bool success = true;
  for (int i = 0; i < 3; ++i)
  {
    in >> sep{ ':' };
    if (!in)
    {
      success = false;
      break;
    }
    std::string keyN = "0";
    in >> keyN;
    if (!in || keyN.substr(0, 3) != "key")
    {
      success = false;
      break;
    }
    int N = keyN[3] - '0';
    switch (N)
    {
    case 1:
      in >> dbl{ input.key1 };
      break;
    case 2:
      in >> bin{ input.key2 };
      break;
    case 3:
      in >> str{ input.key3 };
      break;
    default:
      success = false;
      break;
    }
    if (!in)
    {
      success = false;
      break;
    }
  }
  in >> sep{ ':' } >> sep{ ')' };
  if (success)
  {
    dest = input;
  }
  return in;
}

std::ostream& yakshieva::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard fmtguard(out);
  out << "(";
  out << ":key1 " << DoubleOut{ src.key1 };
  out << ":key2 " << "0b" << (src.key2 == 0 ? "" : "0") << src.key2;
  out << ":key3 \"" << src.key3 << "\":)";
  return out;
}
