#include "dataStruct.hpp"
#include <iomanip>
#include <delimiterI.hpp>
#include <streamGuard.hpp>
#include "keyInput.hpp"

std::istream& kravchenko::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using cDel = DelimiterI< false >;
  using sDel = StringDelimiterI< false >;
  DataStruct temp{ 0, { 0, 0 }, "" };
  const std::size_t KEYS_COUNT = 3;
  in >> cDel{ '(' };
  for (std::size_t i = 0; i < KEYS_COUNT && in; ++i)
  {
    char key = 0;
    in >> sDel{ ":key" } >> key;
    switch (key)
    {
    case '1':
      in >> SignedLLKey{ temp.key1 };
      break;
    case '2':
      in >> ComplexKey{ temp.key2 };
      break;
    case '3':
      in >> StringKey{ temp.key3 };
      break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
  }
  in >> sDel{ ":)" };
  if (in)
  {
    value = temp;
  }
  return in;
}

std::ostream& kravchenko::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << "(:";
  out << "key1 " << value.key1 << "ll:";
  out << "key2 #c(" << value.key2.real() << ' ' << value.key2.imag() << "):";
  out << "key3 \"" << value.key3 << '\"';
  out << ":)";
  return out;
}

bool kravchenko::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 == other.key1)
  {
    if (std::abs(key2) == std::abs(other.key2))
    {
      return key3.size() < other.key3.size();
    }
    return std::abs(key2) < std::abs(other.key2);
  }
  return key1 < other.key1;
}
