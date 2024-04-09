#include "DataStruct.hpp"
#include <iomanip>
#include <cmath>
#include "calcultComplex.hpp"
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
  using delStr = DelimiterStr;
  size_t key = 0;

  in >> del{ '(' };

  for (size_t i = 0; i != 3; i++)
  {
    in >> del{ ':' } >> delStr{ "key" } >> key;
    if (key == 1)
    {
      in >> DoubleKey{ value.key1 };
    }
    else if (key == 2)
    {
      in >> ComplexKey{ value.key2 };
    }
    else if (key == 3)
    {
      in >> StringKey{ value.key3 };
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
  double currComplex = calcultComplex(key2.real(), key2.imag());
  double newComplex =  calcultComplex(value.key2.real(), value.key2.imag());

  if (key1 != value.key1)
  {
    return key1 < value.key1;
  }
  else if (currComplex != newComplex)
  {
    return currComplex < newComplex;
  }
  else
  {
    return (key3.length() <= value.key3.length());
  }
}
