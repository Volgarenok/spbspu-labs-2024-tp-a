#include "dataStruct.hpp"
#include <complex>
#include <iomanip>
#include <ios>
#include <iostream>
#include <delimeter.hpp>
#include <streamGuard.hpp>
#include "keysEnum.hpp"
#include "parsers.hpp"

bool demidenko::DataStruct::operator<(const DataStruct& other) const noexcept
{
  if (key1 == other.key1)
  {
    if (key2 == other.key2)
    {
      return key3.length() < other.key3.length();
    }
    else
    {
      return std::norm(key2) < std::norm(other.key2);
    }
  }
  else
  {
    return key1 < other.key1;
  }
}

std::istream& demidenko::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  using del = DelimeterI;
  KeysEnum current_key = KeysEnum::NONE;
  unsigned int used_keys = 0;

  in >> del{ "(:" };
  for (int i = 0; in && i < 3; i++)
  {
    in >> KeyI{ current_key } >> del{ " " };
    if (current_key & used_keys)
    {
      in.setstate(std::ios::failbit);
    }
    else
    {
      used_keys |= current_key;
    }
    switch (current_key)
    {
    case ULL_OCT:
      in >> UnsignedLongLongI{ data.key1 };
      break;
    case CMP_LSP:
      in >> ComplexI{ data.key2 };
      break;
    case STRING:
      in >> StringI{ data.key3 };
      break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
    in >> del{ ":" };
  }
  in >> del{ ")" };
  if (used_keys != KeysEnum::ALL)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& demidenko::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard guard(out);
  out << std::fixed << std::oct << std::setprecision(1);
  out << "(:key1 0" << data.key1;
  out << ":key2 #c(" << data.key2.real() << ' ' << data.key2.imag() << ')';
  out << ":key3 " << std::quoted(data.key3) << ":)";
  return out;
}
