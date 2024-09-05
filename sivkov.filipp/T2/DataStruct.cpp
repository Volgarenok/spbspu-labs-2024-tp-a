#include "DataStruct.hpp"
#include <iomanip>
#include "Delimiter.hpp"
#include "inputKeys.hpp"

std::istream& sivkov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = DelimiterI;
  size_t count = 0;
  std::string numKey = " ";

  in >> del{ '(' };
  while (in && (count < 3))
  {
    in >> del{ ':' } >> numKey;
    if ((numKey == "key1") && (count != 3))
    {
      in >> DoubleKey{ value.key1 };
      ++count;
    }
    else if ((numKey == "key2") && (count != 3))
    {
      in >> ComplexKey{ value.key2 };
      ++count;
    }
    else if ((numKey == "key3") && (count != 3))
    {
      in >> StringKey{ value.key3 };
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

std::ostream& sivkov::operator<<(std::ostream & out, const DataStruct & value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << std::setprecision(1) << std::fixed;
  out << "(:key1 " << value.key1 << "d";
  out << ":key2 #c(" << value.key2.real() << " " << value.key2.imag() << "):";
  out << "key3 \"" << value.key3 << "\":)";
  return out;
}


bool sivkov::DataStruct::operator<(const DataStruct& value) const
{

  if (key1 != value.key1)
  {
    return key1 < value.key1;
  }
  else if (std::abs(key2) != std::abs(value.key2))
  {
    return std::abs(key2) < std::abs(value.key2);
  }
  else
  {
    return (key3.length() < value.key3.length());
  }
}
