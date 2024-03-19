#include "DataStruct.hpp"
#include <iomanip>
#include "Delimeter.hpp"

std::ostream& kuznetsov::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << data.key1 << "ull";
  out << ":key2 #c(" << std::setprecision(1) << std::fixed << data.key2.real() << " " << data.key2.imag() << ")";
  out << ":key3 \"" << data.key3 << "\":)\n";
  return out;
}

std::istream& kuznetsov::operator>>(std::istream& in, std::string& line)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    char symbol = 0;
    size_t i = 0;
    in >> symbol;
    while (symbol != '\"')
    {
      line += symbol;
      in >> symbol;
    }
  }
  return in;
}

void kuznetsov::inputFromKeyNumber(std::istream& in, DataStruct& data)
{
  using delchr = DelimeterChar;
  using delstr = DelimeterString;
  int keyNumber;
  in >> keyNumber;
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
    double real = 0.0;
    double imag = 0.0;
    in >> delstr{ "#c(" } >> real >> imag >> delchr{ ')' };
    std::complex<double> complexData(real, imag);
    if (in)
    {
      data.key2 = complexData;
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
}

std::istream& kuznetsov::operator>>(std::istream& in, DataStruct& data)
{
  using delchr = DelimeterChar;
  using delstr = DelimeterString;
  in >> delstr{ "(:" };
  for (int i = 0; i < 3; ++i)
  {
    in >> delstr{ "key" };
    inputFromKeyNumber(in, data);
    in >> delchr{ ':' };
  }
  in >> delchr{ ')' };
  return in;
}
