#include "DataStruct.hpp"
#include "Delimiter.hpp"
#include "Keys.hpp"
#include "StreamGuard.hpp"
#include <iomanip>
#include <string>

bool vorobieva::DataStruct::operator<(const DataStruct & value) const
{
  if (key1 != value.key1)
  {
    return std::abs(key1) < std::abs(value.key1);
  }
  else if (key1 == value.key1)
  {
    return key2 < value.key2;
  }
  else
  {
    return key3.length() < value.key3.length();
  }
}

std::istream &vorobieva::operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = DelimiterChar;
  size_t count = 0;
  std::string numKey = "";
  in >> del{ '(' };

  while (in && (count < 3))
  {
    in >> del{ ':' } >> numKey;
    if ((numKey == "key1") && (count != 3))
    {
      in >> ComplexKey{ data.key1 };
      ++count;
    }
    else if ((numKey == "key2") && (count != 3))
    {
      in >> BinaryKey{ data.key2 };
      ++count;
    }
    else if ((numKey == "key3") && (count != 3))
    {
      in >> StringKey{ data.key3 };
      ++count;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> del{ ':' } >> del{ ')' };
  return in;
}

std::ostream & vorobieva::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard fmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << "(:key1 #c(" << data.key1.real() << " " << data.key1.imag() << ")";
  out << ":key2 0b" << (data.key2 == 0 ? "" : "0") << data.key2;
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
}
