#include "datastruct.hpp"
#include "streamguard.hpp"
#include "delimiter.hpp"
#include "formats.hpp"

bool gladyshev::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  else if (key2 != other.key2)
  {
    return key2 < other.key2;
  }
  return key3.size() < other.key3.size();
}

std::istream& gladyshev::operator>>(std::istream& in, DataStruct& value)
{
 std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard StreamGuard(in);
  DataStruct temp = { 0, 0, "" };
  in >> Delimiter{"(:"};
  std::string supstr = "";
  for (size_t i = 0; i < 3; ++i)
  {
    in >> supstr;
    if (supstr == "key1")
    {
      in >> SciKey{temp.key1};
    }
    else if (supstr == "key2")
    {
      in >> CharKey{temp.key2};
    }
    else if (supstr == "key3")
    {
      in >> StrKey{temp.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> Delimiter{":"};
  }
  in >> Delimiter{")"};
  if (in)
  {
    value = temp;
  }
  return in;
}

namespace gladyshev
{
  std::ostream& parseScientific(std::ostream& out, double key)
  {
    int exponent = 0;
    while (key >= 10)
    {
      key /= 10;
      ++exponent;
    }
    while (key < 1)
    {
      key *= 10;
      --exponent;
    }
    if (exponent > 0)
    {
      out << key << 'e' <<  '+' << exponent;
    }
    else
    {
      out << key << 'e' << exponent;
    }
    return out;
  }
}

std::ostream& gladyshev::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard StreamGuard(out);
  out << std::fixed;
  out.precision(1);
  out << "(:key1 ";
  parseScientific(out, value.key1);
  out << ":key2 '" << value.key2 << "':key3 \"" << value.key3 << "\":)";
  return out;
}
