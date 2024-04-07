#include "DataStruct.hpp"
#include <string>
#include <iomanip>
#include "KeyType.hpp"
#include "Streamguard.hpp"
#include "Delimeter.hpp"

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
  DataStruct input;
  using sep = DelimeterIO;
  using dbl = DoubleIO;
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
    std::string keyN;
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

std::ostream& yakshieva::operator << (std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  Streamguard fmtguard(out);
  out << "(";
  out << ":key1 " << std::setprecision(2);
  int exponent = 0;
  double mantissa = src.key1;
  if (mantissa != 0)
  {
    if (mantissa >= 1.0 && mantissa < 10.0)
    {
      out << std::fixed << mantissa;
    }
    else if (mantissa >= 10.0)
    {
      while (mantissa >= 10.0)
      {
        mantissa = mantissa / 10;
	exponent++;
      }
      out << std::fixed << mantissa << 'e' << '+' << exponent;
    }
    else if (mantissa < 1.0)
    {
      while (mantissa < 1.0)
      {
        mantissa = mantissa * 10;
	exponent--;
      }
      out << std::fixed << mantissa << 'e' << exponent;
    }
  }
  else
  {
    out << std::fixed << mantissa;
  }
  out << " :key2 " << "0b" << (src.key2 == 0 ? "" : "0") << src.key2;
  out << " :key3 \"" << src.key3 << "\"";
  out << ":)" << "\n";
  return out;
}

