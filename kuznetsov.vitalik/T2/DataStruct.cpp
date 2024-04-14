#include "DataStruct.hpp"
#include <cmath>
#include <iomanip>
#include "Delimeter.hpp"

bool kuznetsov::DataStruct::operator<(const DataStruct& data) const
{
  if (key1 < data.key1)
  {
    return true;
  }
  else if (key1 > data.key1)
  {
    return false;
  }
  else if (std::abs(key2) < std::abs(data.key2))
  {
    return true;
  }
  else if (std::abs(key2) > std::abs(key2))
  {
    return false;
  }
  return key3.length() < data.key3.length();
}

std::ostream& kuznetsov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << data.key1 << "ull";
  out << ":key2 #c(" << std::setprecision(1) << std::fixed << data.key2.real() << " " << data.key2.imag() << ")";
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
}

std::istream& kuznetsov::operator>>(std::istream& in, unsigned long long&& data)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    in >> data;
  }
  return in;
}

std::istream& kuznetsov::operator>>(std::istream& in, std::complex< double >& data)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    double real = 0.0;
    double imag = 0.0;
    in >> real >> imag;
    std::cout << real << imag;
    data = { real, imag };
  }
  return in;
}

std::istream& kuznetsov::operator>>(std::istream& in, std::string& line)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    std::getline(in, line, '\"');
  }
  return in;
}

std::istream& kuznetsov::operator>>(std::istream& in, DataStruct& data)
{
  using delchr = DelimeterChar;
  using delstr = DelimeterString;
  size_t keyNumber = 0;
  in >> delstr{ "(:" };
  for (int i = 0; i < 3; ++i)
  {
    in >> delstr{ "key" } >> keyNumber;
    if (keyNumber == 1)
    {
      unsigned long long s = 0;
      in >> s >> delstr{ "ull" };
      if (in)
      {
        data.key1 = s;
      }
    }
    else if (keyNumber == 2)
    {
      std::complex< double > newComplex;
      in >> delstr{ "#c(" } >> newComplex >> delchr{ ')' };
      if (in)
      {
        data.key2 = newComplex;
      }
    }
    else if (keyNumber == 3)
    {
      std::string s = "";
      in >> delchr({ '\"' }) >> s;
      if (in)
      {
        data.key3 = s;
      }
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> delchr{ ':' };
  }
  in >> delchr{ ')' };
  return in;
}

